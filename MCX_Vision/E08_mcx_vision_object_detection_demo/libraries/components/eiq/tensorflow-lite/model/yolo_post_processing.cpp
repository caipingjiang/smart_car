/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <cstddef>
#include <cstdint>
#include <math.h>
#include <forward_list>
#include <vector>
#include "yolo_post_processing.h"
#include "fsl_debug_console.h"


namespace yolo {
namespace image {   
  float Calculate1DOverlap(float x1Center, float width1, float x2Center, float width2)
    {
        float left_1 = x1Center - width1/2;
        float left_2 = x2Center - width2/2;
        float leftest = left_1 > left_2 ? left_1 : left_2;

        float right_1 = x1Center + width1/2;
        float right_2 = x2Center + width2/2;
        float rightest = right_1 < right_2 ? right_1 : right_2;

        return rightest - leftest;
    }

    float CalculateBoxIntersect(Box& box1, Box& box2)
    {
        float width = Calculate1DOverlap(box1.x, box1.w, box2.x, box2.w);
        if (width < 0) {
            return 0;
        }
        float height = Calculate1DOverlap(box1.y, box1.h, box2.y, box2.h);
        if (height < 0) {
            return 0;
        }

        float total_area = width*height;
        return total_area;
    }

    float CalculateBoxUnion(Box& box1, Box& box2)
    {
        float boxes_intersection = CalculateBoxIntersect(box1, box2);
        float boxes_union = box1.w * box1.h + box2.w * box2.h - boxes_intersection;
        return boxes_union;
    }

    float CalculateBoxIOU(Box& box1, Box& box2)
    {
        float boxes_intersection = CalculateBoxIntersect(box1, box2);
        if (boxes_intersection == 0) {
            return 0;
        }

        float boxes_union = CalculateBoxUnion(box1, box2);
        if (boxes_union == 0) {
            return 0;
        }

        return boxes_intersection / boxes_union;
    }

    void CalculateNMS(std::forward_list<Detection>& detections, int classes, float iouThreshold)
    {
        int idxClass{0};
        auto CompareProbs = [idxClass](Detection& prob1, Detection& prob2) {
            return prob1.prob[idxClass] > prob2.prob[idxClass];
        };

        for (idxClass = 0; idxClass < classes; ++idxClass) {
            detections.sort(CompareProbs);

            for (auto it=detections.begin(); it != detections.end(); ++it) {
                if (it->prob[idxClass] == 0) continue;
                for (auto itc=std::next(it, 1); itc != detections.end(); ++itc) {
                    if (itc->prob[idxClass] == 0) {
                        continue;
                    }
                    if (CalculateBoxIOU(it->bbox, itc->bbox) > iouThreshold) {
                        itc->prob[idxClass] = 0;
                    }
                }
            }
        }
    }
}  

DetectorPostProcess::DetectorPostProcess(
		const TfLiteTensor** modelOutput,
		std::vector<object_detection::DetectionResult>& results,
		const object_detection::PostProcessParams& postProcessParams)
        :   m_outputTensor{modelOutput},
            m_results{results},
            m_postProcessParams{postProcessParams}
{

    /* Init PostProcessing */

    
    std::vector<object_detection::Branch> branches;
    object_detection::Network net;
    for (int i = 0; i < postProcessParams.output_size; i++) {
    	object_detection::Branch branch = {};
        branch.height = this->m_outputTensor[i]->dims->data[1];
        branch.width = this->m_outputTensor[i]->dims->data[2];
        branch.numBox = 3;
        branch.anchor = postProcessParams.anchors[i];
        
        branch.type = this->m_outputTensor[i]->type;
        if (branch.type == kTfLiteFloat32) {

            branch.modelOutput_f32 = this->m_outputTensor[i]->data.f;

        } else if (branch.type == kTfLiteInt8) {

            branch.modelOutput_int8 = this->m_outputTensor[i]->data.int8;
            branch.scale = (static_cast<TfLiteAffineQuantization*>(this->m_outputTensor[i]->quantization.params))->scale->data[0];
            branch.zeroPoint =(static_cast<TfLiteAffineQuantization*>(this->m_outputTensor[i]->quantization.params))->zero_point->data[0];
        }
        branches.push_back(branch);
    }
    net.inputHeight = postProcessParams.inputImgRows;
    net.inputWidth = postProcessParams.inputImgCols;
    net.numClasses = postProcessParams.numClasses;
    net.branches = branches;
    net.topN = postProcessParams.topN;
    this->m_net = net;
    
    /* End init */
}

bool DetectorPostProcess::DoPostProcess()
{
    /* Start postprocessing */
    int originalImageWidth  = m_postProcessParams.originalImageWidth;
    int originalImageHeight = m_postProcessParams.originalImageHeight;

    std::forward_list<image::Detection> detections;
    GetNetworkBoxes(this->m_net, originalImageWidth, originalImageHeight, m_postProcessParams.threshold, detections);

    /* Do nms */
    CalculateNMS(detections, this->m_net.numClasses, this->m_postProcessParams.nms);

    for (auto& it: detections) {
        float xMin = it.bbox.x - it.bbox.w / 2.0f;
        float xMax = it.bbox.x + it.bbox.w / 2.0f;
        float yMin = it.bbox.y - it.bbox.h / 2.0f;
        float yMax = it.bbox.y + it.bbox.h / 2.0f;

        if (xMin < 0) {
            xMin = 0;
        }
        if (yMin < 0) {
            yMin = 0;
        }
        if (xMax > originalImageWidth) {
            xMax = originalImageWidth;
        }
        if (yMax > originalImageHeight) {
            yMax = originalImageHeight;
        }

        float boxX = xMin;
        float boxY = yMin;
        float boxWidth = xMax - xMin;
        float boxHeight = yMax - yMin;

        for (int j = 0; j < this->m_net.numClasses; ++j) {
        	float score = it.prob[j];
            if ( score > 0 && score < 1.0f) {

                object_detection::DetectionResult tmpResult = {};
                tmpResult.m_normalisedVal = score;
                tmpResult.m_x0 = boxX;
                tmpResult.m_y0 = boxY;
                tmpResult.m_w = boxWidth;
                tmpResult.m_h = boxHeight;
                tmpResult.m_class = j;
                tmpResult.m_score = score;

                this->m_results.push_back(tmpResult);
            }
        }
    }
    return true;
}

void DetectorPostProcess::InsertTopNDetections(std::forward_list<image::Detection>& detections, image::Detection& det)
{
    std::forward_list<image::Detection>::iterator it;
    std::forward_list<image::Detection>::iterator last_it;
    for ( it = detections.begin(); it != detections.end(); ++it ) {
        if(it->objectness > det.objectness)
            break;
        last_it = it;
    }
    if(it != detections.begin()) {
        detections.emplace_after(last_it, det);
        detections.pop_front();
    }
}

float _sigmoid(float x)
{
  return (1/(1 + std::exp(-x)));
}

void DetectorPostProcess::GetNetworkBoxes(
        object_detection::Network& net,
        int imageWidth,
        int imageHeight,
        float threshold,
        std::forward_list<image::Detection>& detections)
{
    int numClasses = net.numClasses;
    int num = 0;
    static int bbox_obj_offset;
     static float objectness;
    auto det_objectness_comparator = [](image::Detection& pa, image::Detection& pb) {
        return pa.objectness < pb.objectness;
    };
    for (size_t i = 0; i < net.branches.size(); ++i) {
        int height   = net.branches[i].height;
        int width    = net.branches[i].width;
        int channel  = net.branches[i].numBox*(5+numClasses);

        for (int h = 0; h < net.branches[i].height; h++) {
            for (int w = 0; w < net.branches[i].width; w++) {
                for (int anc = 0; anc < net.branches[i].numBox; anc++) {

                    /* Objectness score */
                    
                    bbox_obj_offset = h * width * channel + w * channel + anc * (numClasses + 5) + 4;
                    if (net.branches[i].type == kTfLiteFloat32){
                      objectness = _sigmoid(
                              static_cast<float>(net.branches[i].modelOutput_f32[bbox_obj_offset])
                              
                              );

                    } else if (net.branches[i].type == kTfLiteInt8) {
                      objectness =
                          _sigmoid((static_cast<float>(
                                        net.branches[i]
                                            .modelOutput_int8[bbox_obj_offset] -
                                        net.branches[i].zeroPoint) *
                                    net.branches[i].scale));
                    }
                #ifdef WIN32	
                    if (objectness > 0.01)
                      printf("%f:%d,%d,%d\r\n", objectness, h, w, anc);
                #endif
                    if(objectness > threshold) {
                        image::Detection det;
                        det.objectness = objectness;
                        /* Get bbox prediction data for each anchor, each feature point */
                        int bbox_x_offset = bbox_obj_offset -4;
                        int bbox_y_offset = bbox_x_offset + 1;
                        int bbox_w_offset = bbox_x_offset + 2;
                        int bbox_h_offset = bbox_x_offset + 3;
                        int bbox_scores_offset = bbox_x_offset + 5;
                        if (net.branches[i].type == kTfLiteFloat32){
                          det.bbox.x = (static_cast<float>(net.branches[i].modelOutput_f32[bbox_x_offset])
                                  );
                          det.bbox.y = (static_cast<float>(net.branches[i].modelOutput_f32[bbox_y_offset])
                                  );
                          det.bbox.w = (static_cast<float>(net.branches[i].modelOutput_f32[bbox_w_offset])
                                  );
                          det.bbox.h = (static_cast<float>(net.branches[i].modelOutput_f32[bbox_h_offset])
                                  );
                        } else if (net.branches[i].type == kTfLiteInt8) {
                          det.bbox.x =
                              (static_cast<float>(
                                   net.branches[i].modelOutput_int8[bbox_x_offset] -
                               net.branches[i].zeroPoint) *
                               net.branches[i].scale);
                          det.bbox.y =
                              (static_cast<float>(
                                   net.branches[i]
                                       .modelOutput_int8[bbox_y_offset] -
                               net.branches[i].zeroPoint) *
                               net.branches[i].scale);
                          det.bbox.w =
                              (static_cast<float>(
                                   net.branches[i]
                                       .modelOutput_int8[bbox_w_offset] -
                               net.branches[i].zeroPoint) *
                               net.branches[i].scale);
                          det.bbox.h =
                              (static_cast<float>(
                                   net.branches[i]
                                       .modelOutput_int8[bbox_h_offset] -
                               net.branches[i].zeroPoint) *
                               net.branches[i].scale);

                  
                        }

                        float bbox_x, bbox_y;

                        /* Eliminate grid sensitivity trick involved in YOLOv4 */
                        bbox_x = _sigmoid(det.bbox.x);
                        bbox_y = _sigmoid(det.bbox.y);
                        det.bbox.x = (bbox_x + w) / width;
                        det.bbox.y = (bbox_y + h) / height;
						
						//py_tf_debug("%f,%f,%f,%f,%f",objectness,bbox_x,bbox_y,det.bbox.x,det.bbox.y);
                        det.bbox.w = std::exp(det.bbox.w) * net.branches[i].anchor[anc*2] / net.inputWidth;
                        det.bbox.h = std::exp(det.bbox.h) * net.branches[i].anchor[anc*2+1] / net.inputHeight;

                        for (int s = 0; s < numClasses; s++) {
                          if (net.branches[i].type == kTfLiteFloat32) {
                            float sig =
                                _sigmoid(static_cast<float>(
                                    net.branches[i]
                                        .modelOutput_f32[bbox_scores_offset +
                                                         s])) ;
                            sig = sig * objectness;

                            det.prob.push_back((sig > threshold) ? sig : 0);
                          } else if (net.branches[i].type == kTfLiteInt8) {
                          
                            float sig =
                                _sigmoid((static_cast<float>(
                                              net.branches[i].modelOutput_int8
                                                  [bbox_scores_offset + s] -
                                          net.branches[i].zeroPoint) *
                                          net.branches[i].scale));
                            sig = sig * objectness;
                            det.prob.push_back((sig > threshold) ? sig : 0);
                          }
                        }

                        /* Correct_YOLO_boxes */
                        det.bbox.x *= imageWidth;
                        det.bbox.w *= imageWidth;
                        det.bbox.y *= imageHeight;
                        det.bbox.h *= imageHeight;

                        if (num < net.topN || net.topN <=0) {
                            detections.emplace_front(det);
                            num += 1;
                        } else if (num == net.topN) {
                            detections.sort(det_objectness_comparator);
                            InsertTopNDetections(detections, det);
                            num += 1;
                        } else {
                            InsertTopNDetections(detections, det);
                        }
                    }
                }
            }
        }
    }
    if(num > net.topN)
        num -=1;

}
}
