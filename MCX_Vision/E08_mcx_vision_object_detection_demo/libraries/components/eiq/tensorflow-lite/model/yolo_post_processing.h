/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef YOLO_POST_PROCESSING_H
#define YOLO_POST_PROCESSING_H

#include <vector>
#include <forward_list>
#include "tensorflow/lite/c/common.h"

namespace yolo {

namespace image {

    /**
     * Contains the x,y co-ordinates of a box centre along with the box width and height.
     */
    struct Box {
        float x;
        float y;
        float w;
        float h;
    };

    struct Detection {
        Box bbox;
        std::vector<float> prob;
        float objectness;
    };
}

namespace object_detection {

    /**
     * @brief   Class representing a single detection result.
     */
    class DetectionResult {
    public:
        /**
         * @brief       Constructor
         * @param[in]   normalisedVal   Result normalized value
         * @param[in]   x0              Top corner x starting point
         * @param[in]   y0              Top corner y starting point
         * @param[in]   w               Detection result width
         * @param[in]   h               Detection result height
         **/
        DetectionResult(double normalisedVal, float x0, float y0, float w, float h,
                int m_class, float score) :
                m_normalisedVal(normalisedVal),
                m_x0(x0),
                m_y0(y0),
                m_w(w),
                m_h(h),
				m_class(m_class),
				m_score(score)
            {
            }

        DetectionResult() = default;
        ~DetectionResult() = default;

        double  m_normalisedVal{0.0};
		float m_x0{0};
		float m_y0{0};
		float m_w{0};
		float m_h{0};
		int m_class{0};
		float   m_score{0.0f};
    };


    struct PostProcessParams {
        int inputImgRows;
        int inputImgCols;
        int output_size;
        int originalImageWidth;
        int originalImageHeight;

        float threshold;
        float nms;
        int numClasses;
        int topN;
        float anchors[3][6];
        float outs_scale[3];
        int outs_zeroPoint[3];
    };

    struct Branch {
        int width;
        int height;
        int numBox;
        const float* anchor;
        union {
                float* modelOutput_f32;
                int8_t* modelOutput_int8;
            };
        float scale;
        int zeroPoint;
        TfLiteType type;
        size_t size;
    };

    struct Network {
        int inputWidth;
        int inputHeight;
        int numClasses;
        std::vector<Branch> branches;
        int topN;
    };

} /* namespace object_detection */
    
    class BasePostProcess {

    public:
        virtual ~BasePostProcess() = default;

        /**
         * @brief       Should perform post-processing of the result of inference then populate
         *              populate result data for any later use.
         * @return      true if successful, false otherwise.
         **/
        virtual bool DoPostProcess() = 0;
    };
    
    
    class DetectorPostProcess : public BasePostProcess {
    public:
        /**
         * @brief        Constructor.
         * @param[in]    outputTensor0       Pointer to the TFLite Micro output Tensor at index 0.
         * @param[in]    outputTensor1       Pointer to the TFLite Micro output Tensor at index 1.
         * @param[out]   results             Vector of detected results.
         * @param[in]    postProcessParams   Struct of various parameters used in post-processing.
         **/
    	explicit DetectorPostProcess(const TfLiteTensor* outputTensor[],
    									std::vector<object_detection::DetectionResult>& results,
										const object_detection::PostProcessParams& postProcessParams);

        /**
         * @brief    Should perform YOLO post-processing of the result of inference then
         *           populate Detection result data for any later use.
         * @return   true if successful, false otherwise.
         **/
        bool DoPostProcess() override;

    private:
        const TfLiteTensor** m_outputTensor;
        /* Output tensor index 1 */
        std::vector<object_detection::DetectionResult>& m_results;       /* Single inference results. */
        const object_detection::PostProcessParams& m_postProcessParams;  /* Post processing param struct. */
        object_detection::Network m_net;                                 /* YOLO network object. */

        /**
         * @brief       Insert the given Detection in the list.
         * @param[in]   detections   List of detections.
         * @param[in]   det          Detection to be inserted.
         **/
        void InsertTopNDetections(std::forward_list<image::Detection>& detections, image::Detection& det);

        /**
         * @brief        Given a Network calculate the detection boxes.
         * @param[in]    net           Network.
         * @param[in]    imageWidth    Original image width.
         * @param[in]    imageHeight   Original image height.
         * @param[in]    threshold     Detections threshold.
         * @param[out]   detections    Detection boxes.
         **/
        void GetNetworkBoxes(object_detection::Network& net,
                             int imageWidth,
                             int imageHeight,
                             float threshold,
                             std::forward_list<image::Detection>& detections);
    };
    
}
#endif
