#include <stdio.h>

// Free RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ESP bilgilerini çeken kütüphaneler
#include "esp_chip_info.h" //esp_chip_info_t, esp_chip_info()
#include "esp_flash.h" //esp_flash_get_size(), program kalıcı olarak kalır
#include "esp_log.h" //ESP_LOGI()
// ESP_LOGE()  // Error
// ESP_LOGW()  // Warning
// ESP_LOGI()  // Information
// ESP_LOGD()  // Debug
// ESP_LOGV()  // Verbose
#include "esp_system.h" //esp_get_free_heap_size(), esp_get_minimum_free_heap_size() heap ve ram bölgeleriyle ilgili bilgiler
#include "esp_timer.h"

static const char *TAG = "SYSTEM";
// static: değişken yalnızca bu .c dosyası içerisinde kullanılabilir.

void app_main(void)
{
    esp_chip_info_t chip_info; //esp_chip_info_t bir struct türü
    uint32_t flash_size = 0;

    // Çip bilgilerini al
    esp_chip_info(&chip_info);

    // Flash boyutunu al
    esp_flash_get_size(NULL, &flash_size);
    // NULL: ana flash çipi
    // (hangi_cip, sonuc_buraya_yazilacak)

    ESP_LOGI(TAG, "========================================");
    ESP_LOGI(TAG, "        ESP32 SYSTEM INFORMATION");
    ESP_LOGI(TAG, "========================================");

    ESP_LOGI(TAG, "Chip Model       : ESP32");
    ESP_LOGI(TAG, "CPU Cores        : %d", chip_info.cores);
    ESP_LOGI(TAG, "Revision         : %d", chip_info.revision);

    ESP_LOGI(TAG, "Flash size       : %.2f MB", flash_size / (1024.0 * 1024.0));
    
    ESP_LOGI(TAG, "Free Heap        : %lu bytes", esp_get_minimum_free_heap_size());
    
    ESP_LOGI(TAG, "Minimum Heap     : %lu MB", esp_get_minimum_free_heap_size());

    ESP_LOGI(TAG, "IDF Version      : %s", esp_get_idf_version());


    ESP_LOGI(TAG, "========================================");

    while (true)
    {
        int64_t uptime = esp_timer_get_time() / 1000000; // mikrosaniye cinsinden

        ESP_LOGI(TAG,
        "Uptime: %lld sec | Heap: %lu bytes",
        uptime,
        esp_get_free_heap_size());

        vTaskDelay(pdMS_TO_TICKS(1000)); 
        // task.h -> vTaskDelay:   
        // FreeRTOS.h -> pdMS_TO_TICKS: 
    }
}
