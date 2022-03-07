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

int create_interface(KernelPacket &pmsg, int size, int id)
{
  pmsg.ptr = new uint8_t[size];
  pmsg.identifier = id;

  return 0;
}

void destroy_interface(KernelPacket &pmsg)
{
  delete[] pmsg.ptr;
  pmsg.ptr = NULL;
}