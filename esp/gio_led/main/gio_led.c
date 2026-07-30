#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO GPIO_NUM_18

void app_main(void)
{
    // LED HIZLICA YANIP SÖN
    // gpio_reset_pin(LED_GPIO);
    // gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // while (1) {
    //     gpio_set_level(LED_GPIO, 1);
    //     vTaskDelay(pdMS_TO_TICKS(200)); //200ms

    //     gpio_set_level(LED_GPIO, 0);
    //     vTaskDelay(pdMS_TO_TICKS(200));
    
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(LED_GPIO, 0);   // LED sürekli kapalı
}

