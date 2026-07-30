#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "STOPWATCH";

void app_main(void)
{
    ESP_LOGI(TAG, "Saat baslatiliyor.");

    uint32_t sec = 0;
    uint32_t min = 0;
    uint32_t hour = 0;

    while (true)
    {
        ESP_LOGI(
            TAG,
            "%02" PRIu32 ":%02" PRIu32 ":%02" PRIu32,
            hour,
            min,
            sec
        );

        vTaskDelay(pdMS_TO_TICKS(20));

        sec++;

        if (sec >= 60)
        {
            sec = 0;
            min++;
        }

        if (min >= 60)
        {
            min = 0;
            hour++;
        }
    }
}