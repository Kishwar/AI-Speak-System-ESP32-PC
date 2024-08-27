/**
 * @file nv.hpp
 *
 * @brief HAL implementation for SPIFFS and SD Card Init
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 09/02/2022
 *
 */

#include "hal/gpio_types.h"

#include <string>

typedef struct {
  gpio_num_t pin_num_miso;   //<- MISO pin on ESP32
  gpio_num_t pin_num_mosi;   //<- MOSI pin on ESP32
  gpio_num_t pin_num_clk;    //<- CLOCK pin on ESP32
  gpio_num_t pin_num_cs;     //<- CHIP SELECT pin on ESP32
} sdMountInfo;

typedef enum {
  NV_MEMORY_SPIFFS,   //<- Internal memory of ESP32 (SPIFFS)
  NV_MEMORY_SDCARD,   //<- External SD Card memory
  NV_MEMORY_OTHER     //<- Other memory not related to ESP32
} memTypeInfo;

typedef struct {
  size_t maxMemory;
  size_t curMemory;
} memInfo;

/*
 * mountSPIFFS mounts SPIFFS of ESP32
 * 
 *     point       [in]
 *     mount point for spiffs
 * 
 *     returns OK (0) / ERROR (-1)
 */
int mountSPIFFS(const std::string &&point = "/SPIffs");

/*
 * mountSD mounts SD of ESP32
 * 
 *     point       [in]
 *     mount point for SD Card
 * 
 *     pinInfo     [in]
 *     information about SD Card socket pins
 * 
 *     returns OK (0) / ERROR (-1)
 */
int mountSD(const sdMountInfo &pinInfo, const std::string &&point = "/SDCard");

/*
 * mountSD mounts SD of ESP32
 * 
 *     point       [in]
 *     mount point for SD Card
 * 
 *     returns OK (0) / ERROR (-1)
 */
int mountSD(const std::string &&point = "/SDCard");

/*
 * Get information about available memory
 * 
 *     type       [in]
 *     Type of the memory info requested
 * 
 *     returns OK (true) / ERROR (false)
 */
bool getInfo(const memTypeInfo type, memInfo &info);

/*
 * Get mount point for selected memory
 * 
 *     type       [out]
 *     mount point information string
 * 
 *     type       [in]
 *     Type of the memory info requested
 * 
 *     returns OK (true) / ERROR (false)
 */
bool point(std::string &pnt, memTypeInfo type);