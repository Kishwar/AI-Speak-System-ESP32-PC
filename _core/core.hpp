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
#include <string>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "esp_log.h"
#include "interface.hpp"

extern QueueHandle_t xQueue_Receive;
extern QueueHandle_t xQueue_Send;
extern QueueHandle_t xQueue_Ind;

#define LOG_INFO(tag, format, ...) \
  ESP_LOGI(tag, "%06d %s: " format, __LINE__, __func__, ##__VA_ARGS__); \

typedef int (*req_handl) (KernelPacket &);

struct KernelHandler
{
  KernelReq req;
  KernelRsp rsp;
  req_handl hdl;
};

void kernel_core(void);

int kernel_add_to_req_queue(KernelPacket &, int = 10);

//wifi handlers
int kernel_request_handle_wifi_connect(KernelPacket &);
int kernel_request_handle_wifi_disconnect(KernelPacket &);
int kernel_request_handle_wifi_get_ip(KernelPacket &);

#endif // _CORE_HPP_
