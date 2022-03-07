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

#include "core.hpp"

int create_interface(KernelPacket &pmsg, int id);

void destroy_interface(KernelPacket &pmsg);

