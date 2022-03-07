/**
 * @file wifi.hpp
 *
 * @brief HAL implementation for WIFI
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/02/2022
 *
 */

#include <string>
#include "core.hpp"

/*
 * Connect to wifi with given ssid and password
 * Function returns async response with connect success / fail.
 * 
 *     ssid       [in]
 *     network name information to be connected
 * 
 *     password   [in]
 *     password for the given ssid
 */
void wificonnect(std::string &, std::string &);

/*
 * Check if module is connected with WIFI
 * 
 *     returns YES (true) / NO (false)
 */
bool isconnected(void);

/*
 * Get information about IP address
 * 
 *     ip       [in]
 *     string object to get update ip value in ipv4 format
 * 
 *     returns OK (true) / ERROR (false)
 */
bool getLocalIP(std::string ip);

int kernel_request_handle_wifi_disconnect(std::string &ssid);

int kernel_request_handle_wifi_get_ip(std::string &ip);