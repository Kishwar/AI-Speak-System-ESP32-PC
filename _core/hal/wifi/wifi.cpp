/**
 * @file wifi.cpp
 *
 * @brief HAL implementation for WIFI
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 13/02/2022
 *
 */

#include "wifi.hpp"

#include "esp_wifi.h"
#include "nvs_flash.h"

#include <cstring>

static bool _isConnected = false;
static std::string _ipAddress;

void wificonnect(std::string &ssid, std::string &password)
{
  wifi_config_t sta_config;
  esp_err_t ret = nvs_flash_init();

  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    nvs_flash_erase();
    nvs_flash_init();
  }

  esp_netif_init();
  esp_event_loop_create_default();
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);

  esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
          [](void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) -> void
          {
            // TODO update information in kernel queue
            if (event_base != WIFI_EVENT) return;
            switch(event_id)
            {
              case WIFI_EVENT_STA_START:
                esp_wifi_connect();
                break;
              case WIFI_EVENT_STA_CONNECTED:
                _isConnected = true;
                break;
              case WIFI_EVENT_STA_DISCONNECTED:
                _isConnected = true;
                break;
              default:
                break;
            }
          }, NULL);

  esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
          [](void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) -> void
          {
            if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
              ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
              _ipAddress = std::to_string(esp_ip4_addr1_16(&event->ip_info.ip)) +
                      ":" + std::to_string(esp_ip4_addr2_16(&event->ip_info.ip)) +
                      ":" + std::to_string(esp_ip4_addr3_16(&event->ip_info.ip)) +
                      ":" + std::to_string(esp_ip4_addr4_16(&event->ip_info.ip));
            }
          }, NULL);

  esp_wifi_set_mode(WIFI_MODE_STA);

  std::memset(&sta_config, 0, sizeof(sta_config));
  std::memcpy(sta_config.sta.ssid, ssid.c_str(), ssid.size());
  std::memcpy(sta_config.sta.password, password.c_str(), password.size());

  esp_wifi_set_config(WIFI_IF_STA, &sta_config);
  esp_wifi_start();
}

bool isconnected(void)
{
  return _isConnected;
}

bool getLocalIP(std::string ip)
{
  if(_ipAddress.size() > 8 /* min ipv4 size */) {
    ip = _ipAddress;
    return true;
  }

  return false;
}

int kernel_request_handle_wifi_disconnect(std::string &ssid)
{
  return 0;
}

int kernel_request_handle_wifi_get_ip(std::string &ip)
{
  return 0;
}