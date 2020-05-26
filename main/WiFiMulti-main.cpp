/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "WiFiMulti-idf.h"

void app_main()
{
    //Initialize NVS --- 
    // NOTE! Does this clear NVS? Or just init access? Looks like gives access because it clears it if there are problems
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Since this seems to be working, set the log level to warning instead of info
    wifi_multi_loglevel_set(TAG, ESP_LOG_INFO);
    ESP_LOGI(TAG, "ESP_WIFI_MODE_INIT_STA");

    // in ESP-IDF is seems there are about 8 tasks
    uint16_t initial_tasks = uxTaskGetNumberOfTasks();

    wifi_multi_start();
    
    wifi_multi_ap_add("sisyphus", "!medea4u");
    wifi_multi_ap_add("bb-ap-x", "landshark");
    wifi_multi_ap_add("laertes", "!medea4u");
    // put this back, it's a good idea, just right now it's also the above one
    //wifi_multi_ap_add(EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

    // wait till they stop
    while(1) {

      uint16_t n_tasks = uxTaskGetNumberOfTasks();

      /* let's see how many tasks exist, and terminate when they go away */
      /* future method will be to create a queue and signal back on death */
      // the interesting bit about this talks about the 'idle task' which will
      // reap deleted tasks... it it out there? Did I need to configure
      // something to start it?
      ESP_LOGD(TAG,"tasks remaining: %u waiting for %u\n",n_tasks,initial_tasks);

      if (n_tasks == initial_tasks) {
        printf("my tasks must have died --- let's restart!\n");
        fflush(stdout);
        esp_restart();
      }

      vTaskDelay(5000 / portTICK_PERIOD_MS);

    }
}
