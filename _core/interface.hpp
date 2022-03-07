/**
 * @file interface.hpp
 *
 * @brief Interface response to connect Kernel with other Apps
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 04/03/2022
 *
 */

#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

#include <stdint.h>

enum KernelReq {
  KERNEL_REQUEST_CONNECT_TO_WIFI_REQ,
  KERNEL_REQUEST_DISCONNECT_WIFI_REQ,
  KERNEL_REQUEST_GET_WIFI_IP_REQ,
  KERNEL_REQUEST_INVALID_VALUE_REQ = 0xFF
};

enum KernelRsp {
  KERNEL_REQUEST_CONNECT_TO_WIFI_RSP,
  KERNEL_REQUEST_DISCONNECT_WIFI_RSP,
  KERNEL_REQUEST_GET_WIFI_IP_RSP,
  KERNEL_REQUEST_INVALID_VALUE_RSP = 0xFF
};

struct KernelPacket
{
  int identifier;
  void *ptr;
  uint32_t ptr_len;
};

int create_interface(KernelPacket &pmsg, int id);

void destroy_interface(KernelPacket &pmsg);

int send_recv_interface_sync(int id, KernelPacket &req, KernelPacket &rsp);

#endif // _INTERFACE_HPP_