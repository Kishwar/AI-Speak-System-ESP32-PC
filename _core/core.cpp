/**
 * @file core.cpp
 *
 * @brief Core implementation of Kernel
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/02/2022
 *
 */

#include "core.hpp"
#include "wifi.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char TAG[] = "CORE_KERNEL";

static const int RECEIVE_QUEUE_LENGTH = 10;
static const int SEND_QUEUE_LENGTH = 10;
#if 0 //not implemented
static const int IND_QUEUE_LENGTH = 15;
#endif

BaseType_t xTask_Receive = pdFAIL;
BaseType_t xTask_Send = pdFAIL;
#if 0 //not implemented
BaseType_t xTask_Ind = pdFAIL;
#endif

QueueHandle_t xQueue_Receive = NULL;
QueueHandle_t xQueue_Send = NULL;
#if 0 //not implemented
QueueHandle_t xQueue_Ind = NULL;
#endif

static void _handle_recv(KernelPacket &ptr);

#define CHECK_TRUE(x) \
  if(!(x)) { \
    LOG_INFO(TAG, "Check failed."); \
    configASSERT(!(x)); \
  } \

KernelHandler hdl[] = {
  //wifi connect
  KERNEL_REQUEST_CONNECT_TO_WIFI_REQ,
  KERNEL_REQUEST_CONNECT_TO_WIFI_RSP,
  kernel_request_handle_wifi_connect,

  //wifi disconnect
  KERNEL_REQUEST_DISCONNECT_WIFI_REQ,
  KERNEL_REQUEST_DISCONNECT_WIFI_RSP,
  kernel_request_handle_wifi_disconnect,

  //wifi get ip
  KERNEL_REQUEST_GET_WIFI_IP_REQ,
  KERNEL_REQUEST_GET_WIFI_IP_RSP,
  kernel_request_handle_wifi_get_ip,

  //write

  //read

};

static void _thread_received(void *ptr)
{
  KernelPacket recv;
  while(true) {
    if(xQueueReceive(xQueue_Receive, &recv, portMAX_DELAY) == pdPASS) {
      
      //handle recv
      _handle_recv(recv);

      //clear memory
      if(recv.ptr != NULL) free(recv.ptr);
    }
  }
}

static void _thread_send(void *ptr)
{
  while(true) {

  }
}

#if 0 //not implemented
static void _thread_ind(void *ptr)
{
  while(true) {

  }
}
#endif

// Kernel thread starting point
void kernel_core(void)
{
  esp_log_level_set(TAG, ESP_LOG_INFO);

  LOG_INFO(TAG, "kernel_core thread starting ...");

  //start receive queue & thread
  xQueue_Receive = xQueueCreate(RECEIVE_QUEUE_LENGTH, sizeof(KernelPacket));
  CHECK_TRUE(xQueue_Receive != NULL);
  LOG_INFO(TAG, "xQueue_Receive created..");

  xTask_Receive = xTaskCreate(_thread_received, "THREAD_RECIVED", 4096, NULL, 20, NULL);
  CHECK_TRUE(xTask_Receive == pdPASS);
  LOG_INFO(TAG, "xTask_Receive created..");

  //start send queue & thread
  xQueue_Send = xQueueCreate(SEND_QUEUE_LENGTH, sizeof(KernelPacket));
  CHECK_TRUE(xQueue_Send != NULL);
  LOG_INFO(TAG, "xQueue_Send created..");

  xTask_Send = xTaskCreate(_thread_send, "THREAD_SEND", 4096, NULL, 20, NULL);
  CHECK_TRUE(xTask_Send == pdPASS);  
  LOG_INFO(TAG, "xTask_Send created..");

#if 0 //not implemented
  //start indication queue & thread
  xQueue_Ind = xQueueCreate(IND_QUEUE_LENGTH, sizeof(KernelPacket));
  CHECK_TRUE(xQueue_Ind != NULL);
  LOG_INFO(TAG, "xQueue_Ind created..");

  xTask_Ind = xTaskCreate(_thread_ind, "THREAD_IND", 4096, NULL, 20, NULL);
  CHECK_TRUE(xTask_Ind == pdPASS);
  LOG_INFO(TAG, "xTask_Ind created..");
#endif

  LOG_INFO(TAG, "kernel_core queues and threads started ...");
}

void _handle_recv(KernelPacket &ptr)
{
  LOG_INFO(TAG, "received message %d", ptr.identifier);
  int len = sizeof(hdl) / sizeof(hdl[0]);
  int i = 0;
  while(i < len) {
    if(hdl[i].req == ptr.identifier) {
      //handle the case here
      hdl[i].hdl(ptr);
      break;
    }
    i += abs(ptr.identifier - hdl[i].req);
  }
}

int kernel_add_to_req_queue(KernelPacket &req, int timeout)
{
  LOG_INFO(TAG, "received message %d", req.identifier);

  //we just need to wait for default=10 ticks
  if(xQueueSend(xQueue_Receive, &req, timeout) == pdPASS) {
    return 0;
  }

  return -1;
}

// ------- interface handlers for different tasks ----
int kernel_request_handle_wifi_connect(KernelPacket &v)
{
  interface_wifi_connect_req *req;
  LOG_INFO(TAG, "%d", v.identifier);

  req = reinterpret_cast<interface_wifi_connect_req *>(v.ptr);
  
  if(req != NULL) {
    wificonnect(req->ssid, req->pass);
  }
  return 0;
}

int kernel_request_handle_wifi_disconnect(KernelPacket &v)
{
  return 0;
}

int kernel_request_handle_wifi_get_ip(KernelPacket &v)
{
  return 0;
}
