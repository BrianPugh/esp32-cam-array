#ifndef PROJECT_LED_HAL_H__
#define PROJECT_LED_HAL_H__

#include "esp_err.h"
#include "sdkconfig.h"
#include "stdbool.h"

/* On the ESP32-CAM, the LED is ON when gpio 33 is low */
#define INDICATOR_LED_ON false
#define INDICATOR_LED_OFF true

/****
 * Setup hardware for LED.
 * Call this once in main()
 */
esp_err_t led_setup();


/**
 * Set LED Value
 */
esp_err_t led_set(bool val);

/***
 * Get LED Value
 */
bool led_get();

/****
 * Toggle LED
 */
esp_err_t led_toggle();

#endif
