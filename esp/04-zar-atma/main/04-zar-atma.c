#include <stdbool.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_random.h"

static const char *TAG = "DICE";

void app_main(void)
{
    ESP_LOGI(TAG, "Dijital zar baslatildi.");

    while (true){
        uint32_t random_number = esp_random(); //rastgele uint_type 
        uint32_t dice = (random_number % 6) + 1;
        const char *even_odd;

        if (dice % 2 == 0){
            even_odd = "Çift";
        }else{
            even_odd = "Tek";
        }

        ESP_LOGI(TAG,
                "Ham rastgele sayi: %lu \t| Zar sonucu : %lu \t| %s",
                random_number,
                dice,
                even_odd);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
