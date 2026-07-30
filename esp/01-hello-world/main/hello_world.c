#include <stdio.h> //standart input output
#include "freertos/FreeRTOS.h" //
#include "freertos/task.h" //
#include "esp_log.h" //

static const char *TAG = "MERHABA";

void app_main(void)
{
    int sayac = 0;

    while (true) {
        ESP_LOGI(TAG, "ESP32 çalışıyor. Sayaç: %d", sayac++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}