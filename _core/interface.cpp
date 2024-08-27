/**
 * @file interface.cpp
 *
 * @brief Interface response to connect Kernel with other Apps
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 04/03/2022
 *
 */

#include "interface.hpp"
#include "core.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void start_interface(void)
{
  kernel_core();
}

int create_interface(KernelPacket &pmsg, int size, int id)
{
  pmsg.ptr = new uint8_t[size];
  pmsg.identifier = id;

  return 0;
}

void destroy_interface(KernelPacket &pmsg)
{
  delete[] static_cast<uint8_t *>(pmsg.ptr);
  pmsg.ptr = NULL;
}

int send_interface_async(KernelPacket &req, int timeout)
{
  return kernel_add_to_req_queue(req, timeout);
}
