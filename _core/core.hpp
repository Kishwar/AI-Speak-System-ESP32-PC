/**
 * @file core.hpp
 *
 * @brief Core implementation of Kernel
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/02/2022
 *
 */

#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <stdint.h>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

extern QueueHandle_t xQueue_Receive;
extern QueueHandle_t xQueue_Send;
extern QueueHandle_t xQueue_Ind;

enum KernelReq {
  KERNEL_REQUEST_CONNECT_TO_WIFI_REQ,
  KERNEL_REQUEST_DISCONNECT_WIFI_REQ,
  KERNEL_REQUEST_GET_WIFI_IP_REQ,
};

enum KernelRsp {
  KERNEL_REQUEST_CONNECT_TO_WIFI_RSP,
  KERNEL_REQUEST_DISCONNECT_WIFI_RSP,
  KERNEL_REQUEST_GET_WIFI_IP_RSP,
};

struct KernelPacket
{
  int identifier;
  uint8_t *ptr;
  uint32_t ptr_len;
};

typedef int (*req_handl) (KernelPacket &);

struct KernelHandler
{
  KernelReq req;
  KernelRsp rsp;
  req_handl hdl;
};

void kernel_core(void *ptr);

#endif // _CORE_HPP_
