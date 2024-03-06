/*
 * File      : dma.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */


/*********************************************************************************************************
**   ͷ�ļ�
*********************************************************************************************************/
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "dma.h"


/*********************************************************************************************************
**   ȫ�ֱ���
*********************************************************************************************************/


/*********************************************************************************************************
**   �궨��
*********************************************************************************************************/
#define DMA_DEBUG 0
#if DMA_DEBUG
#include <stdio.h>
#define DMA_DBG(...) rt_kprintf("[DMA]"),rt_kprintf(__VA_ARGS__)
#else
#define DMA_DBG(...)
#endif



#define __DMA_CHANNEL_RESET(dmac)  do {                           \
            if (dmac->ops && dmac->ops->reset) {\
                dmac->ops->reset(dmac);      \
            }                                                    \
        } while (0)

#define __DMA_CHANNEL_TRANS(dmac, message, ret)  do {           \
            if (dmac->ops && dmac->ops->trans) {                \
                ret = dmac->ops->trans(dmac, message);          \
            }                                                    \
        } while (0)

#define __DMA_CHANNEL_STATUS(ch, ret)  do {                     \
            if (dmac->ops && dmac->ops->status) {\
                ret = dmac->ops->status(dmac);      \
            }                                                    \
        } while (0)


/*********************************************************************************************************
**   ȫ�ֱ���
*********************************************************************************************************/
struct rt_dma_channel   _g_dma_chan_head;
static rt_bool_t        rt_dma_init_flag = RT_FALSE;

/*********************************************************************************************************
** ��������: _dma_init
** ��������: ��ʼ�� DMA
** �䡡  ��: void
** ��    ��: void
** ��    ע: NONE
*********************************************************************************************************/
void  _dma_init (void)
{
    _g_dma_chan_head.ch = -1;
    rt_list_init(&(_g_dma_chan_head.list));
} /* _dma_init */


/*********************************************************************************************************
** ��������: rt_dma_drv_install
** ��������: DMA ͨ����������װ
** �䡡  ��: rt_uint32_t channel,RT_DMA_FUNCS* funcs,rt_size_t maxBurstBytes
** ��    ��: rt_err_t
** ��    ע: NONE
*********************************************************************************************************/
rt_err_t rt_dma_drv_install(struct rt_dma_channel *dmac, struct dma_ops *ops,struct dma_config *config,void* user_data)
{
    /* ������� */
    RT_ASSERT(dmac != RT_NULL);

    if(rt_dma_init_flag == RT_FALSE)
    {
        rt_dma_init_flag = RT_TRUE;

        _dma_init();
    }

    if(ops == RT_NULL)
    {
        DMA_DBG("dma param invalid.\r\n");

        return -RT_EIO;
    }
    /* ���ص�ͨ���б� */
    rt_list_insert_after(&(_g_dma_chan_head.list),&(dmac->list));

    dmac->ops   = ops;
    if(config != RT_NULL)
    {
        dmac->config.direction      = config->direction;
        dmac->config.src_addr_width = config->src_addr_width;
        dmac->config.src_maxburst   = config->src_maxburst;
        dmac->config.dst_addr_width = config->dst_addr_width;
        dmac->config.dst_maxburst   = config->dst_maxburst;
    }

    dmac->user_data = user_data;
    rt_memset(dmac->msg_list,0,RT_DMA_MAX_NODES * sizeof(struct dma_message));
    __DMA_CHANNEL_RESET(dmac);
    return RT_EOK;
}

struct rt_dma_channel *rt_dma_get_channel(int id)
{
    struct rt_dma_channel *dmac;
    struct rt_list_node *node;

    for (node = _g_dma_chan_head.list.next;  node != &(_g_dma_chan_head.list); node = node->next)
    {
        dmac = rt_list_entry(node, struct rt_dma_channel, list);

        if(dmac->ch == id)
            return dmac;
    }

    return RT_NULL;
}
//
///*********************************************************************************************************
//** ��������: rt_dma_flush
//** ��������: ɾ�����б��ӳٴ���Ĵ������� (�����ûص�����)
//** �䡡  ��: rt_uint32_t channel
//** ��    ��: rt_err_t
//** ��    ע: NONE
//*********************************************************************************************************/
//rt_err_t  rt_dma_flush (struct rt_dma_channel *dmac)
//{
//    rt_size_t data_size;
//    struct dma_message *last_message,*message;
//    rt_uint16_t next_index;
//    /* ������� */
//    RT_ASSERT(dmac != RT_NULL);
//
//
//    next_index = dmac->get_index + 1;
//    if(next_index >= RT_DMA_MAX_NODES)
//        next_index = 0;
//
//
////    while (rt_data_queue_pop(&(dmac->tmsg_queue),(const void **)&message, &data_size, 0) == RT_EOK)
////    {
////        /* ��� DMA��Ϣ */
//////        if(message->release_cb != RT_NULL)
//////            message->release_cb(dmac,message);
////    }
//
//    __DMA_CHANNEL_RESET(dmac);
//
////    dmac->tmsg_actived = RT_FALSE;
//    return RT_EOK;
//}

/*********************************************************************************************************
** ��������: rt_dma_trans_message
** ��������: ��� һ��DMA����
** �䡡  ��: rt_uint32_t channel DMA_MSG *pMsg
** ��    ��: rt_err_t
** ��    ע: NONE
*********************************************************************************************************/
rt_err_t  rt_dma_trans_message (struct rt_dma_channel *dmac,struct dma_message* message)
{
    rt_base_t   level;
    rt_err_t    result;
    rt_uint16_t  next_index;
    struct dma_message *msg_node;
    /* ������� */
    RT_ASSERT(dmac != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    RT_ASSERT(message->t_size <= (64 * 1024));

    if(message->t_size == 0)
    {
        if (dmac->complete != RT_NULL)
        {
        	dmac->complete(dmac, message);
        }
        return RT_EOK;
    }

    //�жϴ�������Ƿ���
    next_index = dmac->put_index + 1;
    if(next_index >= RT_DMA_MAX_NODES)
        next_index = 0;
    if(next_index == dmac->get_index)
        return -RT_ENOMEM;

    level = rt_hw_interrupt_disable();

    msg_node = &(dmac->msg_list[dmac->put_index]);
    dmac->put_index = next_index;

    //����message
    rt_memcpy(msg_node,message,sizeof(struct dma_message));

    next_index = dmac->get_index + 1;
    if(next_index >= RT_DMA_MAX_NODES)
        next_index = 0;
    /* check message list whether is empty */
    if(next_index == dmac->put_index)
    {
        rt_hw_interrupt_enable(level);
        /* Make a DMA transfer */
        if(dmac->start != RT_NULL)
        	dmac->start(dmac,message);

        do{
            int ret;
            __DMA_CHANNEL_TRANS(dmac, message, ret);             /*  ��ʼ��������Ԫ              */
            (void)ret;
        } while (0);
    }
    else
    {
        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

/*********************************************************************************************************
** ��������: rt_dma_configture
** ��������: DMA ͨ������
** �䡡  ��: struct rt_dma_channel *dmac,struct dma_config *config
** ��    ��: rt_err_t
** ��    ע: NONE
*********************************************************************************************************/
rt_err_t  rt_dma_configture (struct rt_dma_channel *dmac,struct dma_config *config)
{
    /* ������� */
    RT_ASSERT(dmac != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    dmac->config.direction      = config->direction;
    dmac->config.src_addr_width = config->src_addr_width;
    dmac->config.src_maxburst   = config->src_maxburst;
    dmac->config.dst_addr_width = config->dst_addr_width;
    dmac->config.dst_maxburst   = config->dst_maxburst;

    __DMA_CHANNEL_RESET(dmac);

    return RT_EOK;
} /* rt_dma_configture */

/*********************************************************************************************************
** ��������: rt_dma_get_current_message
** ��������: DMA ��ȡ��ǰ�������Ϣ���
** �䡡  ��: struct rt_dma_channel *dmac
** ��    ��:  struct dma_message *
** ��    ע: NONE
*********************************************************************************************************/
struct dma_message *  rt_dma_get_current_message (struct rt_dma_channel *dmac)
{
    rt_base_t   level;
    struct dma_message *message;

    level = rt_hw_interrupt_disable();

    message = &(dmac->msg_list[dmac->get_index]);

    rt_hw_interrupt_enable(level);
    return message;
} /* rt_dma_get_current_message */

/*********************************************************************************************************
** ��������: rt_dma_contex_service
** ��������: DMA �жϷ���
** �䡡  ��: rt_uint32_t channel
** ��    ��: rt_err_t
** ��    ע: global
*********************************************************************************************************/
rt_err_t rt_dma_contex_service (struct rt_dma_channel *dmac,rt_uint32_t event)
{
    rt_base_t   level;
    rt_size_t data_size;
    struct dma_message *last_message,*message;
    rt_uint16_t next_index;

    /* ������� */
    RT_ASSERT(dmac != RT_NULL);
    switch (event)
    {
    case RT_DMA_EVENT_COMPLETE:
        next_index = dmac->get_index + 1;
        if(next_index >= RT_DMA_MAX_NODES)
            next_index = 0;

        level = rt_hw_interrupt_disable();
        /* ���ȷ��� �������е���Ϣ */
        last_message = &(dmac->msg_list[dmac->get_index]);
        dmac->get_index = next_index;
        if(dmac->get_index != dmac->put_index)
        {
            /* ����������Ϣδ���ͣ����ȴ��� */
            message = &(dmac->msg_list[dmac->get_index]);

            rt_hw_interrupt_enable(level);
            /* Make a DMA transfer */
            if(dmac->start != RT_NULL)
            	dmac->start(dmac,message);

            do{
                int ret;
                __DMA_CHANNEL_TRANS(dmac, message, ret);             /*  ��ʼ��������Ԫ              */
                (void)ret;
            } while (0);
        }
        else
        {
            rt_hw_interrupt_enable(level);
        }

        /* ������һ����Ϣ�Ļص����� */
        if (dmac->complete != RT_NULL)
        {
        	dmac->complete(dmac, last_message);
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}
