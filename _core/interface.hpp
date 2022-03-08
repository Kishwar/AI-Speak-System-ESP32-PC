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
#include <string>

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

void start_interface(void);

int create_interface(KernelPacket &, int, int);

void destroy_interface(KernelPacket &);

int send_interface_async(KernelPacket &, int = 10);

// ----- req / rsp for different tasks ------
struct interface_wifi_connect_req
{
  std::string ssid;
  std::string pass;
};

struct interface_wifi_connect_rsp
{
  int result;
  std::string ip;
};

#endif // _INTERFACE_HPP_
