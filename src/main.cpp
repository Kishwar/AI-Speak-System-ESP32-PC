
#include "interface.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_task_wdt.h"
#include "soc/rtc_wdt.h"
#include "esp_log.h"

extern "C" void app_main() {

  esp_task_wdt_init(portMAX_DELAY, pdFALSE);
  
  start_interface();
#if 1
  {
    //connect to wifi (test)
    KernelPacket v;
    interface_wifi_connect_req *req;

    create_interface(v, sizeof(interface_wifi_connect_req), KERNEL_REQUEST_CONNECT_TO_WIFI_REQ);
    
    req = reinterpret_cast<interface_wifi_connect_req *>(v.ptr);
    req->ssid = "";
    req->pass = "";

    send_interface_async(v);
  }
#endif
  while(1) {
    ESP_LOGI("MAIN", "LOOP...\n");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
