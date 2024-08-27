/**
 * @file nv.cpp
 *
 * @brief HAL implementation for SPIFFS and SD Card Init
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 09/02/2022
 *
 */

#include "nv.hpp"

#include <stddef.h>
#include <cstring>

#include "esp_err.h"
#include "esp_spiffs.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

static bool _spiffs_initialized = false;
static bool _sdffs_initialized = false;
static std::string _spi_point;
static std::string _sd_point;

int mountSPIFFS(const std::string &&point)
{
  if(_spiffs_initialized == true) return 0; // spiffs already initialized

  esp_vfs_spiffs_conf_t conf = {
      .base_path = point.c_str(),
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };
  
  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK) return -1;

  _spi_point = point;

  _spiffs_initialized = true;
  return 0;
}

int mountSD(const sdMountInfo &pinInfo, const std::string &&point)
{
  if(_sdffs_initialized == true) return 0;     // sdffs already initialized

  esp_vfs_fat_sdmmc_mount_config_t mountConfig = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };

  sdmmc_host_t host = {
    .flags = SDMMC_HOST_FLAG_SPI,
    .slot = 1,
    .max_freq_khz = SDMMC_FREQ_DEFAULT,
    .io_voltage = 3.3f,
    .init = &sdspi_host_init,
    .set_bus_width = NULL,
    .get_bus_width = NULL,
    .set_bus_ddr_mode = NULL,
    .set_card_clk = &sdspi_host_set_card_clk,
    .do_transaction = &sdspi_host_do_transaction,
    .deinit_p = &sdspi_host_remove_device,
    .io_int_enable = &sdspi_host_io_int_enable,
    .io_int_wait = &sdspi_host_io_int_wait,
    .command_timeout_ms = 0
  };

  sdmmc_card_t *card;

  sdspi_slot_config_t slotConfig = SDSPI_SLOT_CONFIG_DEFAULT();
  slotConfig.gpio_miso = pinInfo.pin_num_miso;
  slotConfig.gpio_mosi = pinInfo.pin_num_mosi;
  slotConfig.gpio_sck = pinInfo.pin_num_clk;
  slotConfig.gpio_cs = pinInfo.pin_num_cs;

  if(esp_vfs_fat_sdmmc_mount(point.c_str(), &host, &slotConfig, &mountConfig, &card) != ESP_OK) {
    return -1;
  }

  //print card info
  sdmmc_card_print_info(stdout, card);

  _sd_point = point;

  _sdffs_initialized = true;
  return 0;
}

int mountSD(const std::string &&point)
{
  sdMountInfo sdMountPoint = {  .pin_num_miso = GPIO_NUM_2,
                        .pin_num_mosi = GPIO_NUM_15,
                        .pin_num_clk = GPIO_NUM_14,
                        .pin_num_cs = GPIO_NUM_13
                      };

  return mountSD(sdMountPoint, std::move(point));
}

bool getInfo(const memTypeInfo type, memInfo &info)
{
  bool ret{false};

  switch(type)
  {
    case NV_MEMORY_SPIFFS:
      esp_spiffs_info(NULL, &info.maxMemory, &info.curMemory) == ESP_OK ? 
                                                      ret = true : ret = false;
      break;

    default:
      ret = false;
      break;
  }

  return ret;
}

bool point(std::string &pnt, memTypeInfo type)
{
  bool ret{false};

  switch(type)
  {
    case NV_MEMORY_SPIFFS:
      if(_spiffs_initialized == true) {
        pnt = _spi_point;
        ret = true;
      } else {
        ret = false;
      }
      break;

    case NV_MEMORY_SDCARD:
      if(_sdffs_initialized == true) {
        pnt = _sd_point;
        ret = true;
      } else {
        ret = false;
      }
      break;

    default:
      break;
  }

  return ret;
}