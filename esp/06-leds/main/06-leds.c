#include "driver/gpio.h" // pin giriş çıkış
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_PIN GPIO_NUM_27
#define LED_COUNT 5

static const char *TAG = "BUTTON_LED";

static const gpio_num_t leds[LED_COUNT] = {
    GPIO_NUM_18,
    GPIO_NUM_19,
    GPIO_NUM_21,
    GPIO_NUM_22,
    GPIO_NUM_23
};



// LED PİNLERİNİ HAZIRLAR
static void init_leds(void)
{
    uint64_t pin_mask = 0; // ayarlanacak pin

    for (int i = 0; i < LED_COUNT; i++) {  // sırayla seçilen pini 1 yapar
        pin_mask |= (1ULL << leds[i]); 
    }

    gpio_config_t led_config = {
        .pin_bit_mask = pin_mask, // ayarlanacak pinler
        .mode = GPIO_MODE_OUTPUT, // pini output yapar
        .pull_up_en = GPIO_PULLUP_DISABLE, // dahili pull up kapaLı
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // dahili pull down kapalı
        .intr_type = GPIO_INTR_DISABLE // kesme kapalı 
    };

    ESP_ERROR_CHECK(gpio_config(&led_config));

    // tüm ledleri başlangıçta 0 yani kapalı yapar
    for (int i = 0; i < LED_COUNT; i++) {
        gpio_set_level(leds[i], 0);
    }
}

// BUTONU HAZIRLAR
static void init_button(void)
{
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN), //pin GPIO27
        .mode = GPIO_MODE_INPUT, // pin input oldu 
        .pull_up_en = GPIO_PULLUP_ENABLE, // dahili pull up açık
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // dahili pull down kapalı
        .intr_type = GPIO_INTR_DISABLE // kesme kapalı
    };

    ESP_ERROR_CHECK(gpio_config(&button_config));
}


// bir ledi yakar
static void show_only_one_led(int index)
{
    for (int i = 0; i < LED_COUNT; i++) {
        gpio_set_level(leds[i], (i == index) ? 1 : 0);
    }
}

void app_main(void)
{
    init_leds();
    init_button();

    int current_led = 0; // başta led: led[0] = GPIO18
    int last_button_state = 1; // başta 1 kabul ediliyor buton

    show_only_one_led(current_led); 

    ESP_LOGI(TAG, "Sistem basladi");

    while (true) {
        int button_state = gpio_get_level(BUTTON_PIN); // o anda butona basılıyor mu basılmıyor mu POLLING

        if (last_button_state == 1 && button_state == 0) { // buton durumu değiştiyse
            current_led++; // bir sonraki eld

            if (current_led >= LED_COUNT) { // led indexi 5'i geçerse başa dönecek -> 0 
                current_led = 0;
            }

            show_only_one_led(current_led); // ledi yak

            ESP_LOGI(TAG, "Butona basıldı. Yanan LED: %d | GPIO: %d",
                     current_led, leds[current_led]);

            vTaskDelay(pdMS_TO_TICKS(200));
        }

        last_button_state = button_state;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}