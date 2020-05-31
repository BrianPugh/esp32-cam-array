#include "esp_pm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "camera.h"


#define CAM_PIN_PWDN    32
#define CAM_PIN_RESET   -1 //software reset will be performed

#define CAM_PIN_XCLK    0
#define CAM_PIN_SIOD    26
#define CAM_PIN_SIOC    27

#define CAM_PIN_D7      35
#define CAM_PIN_D6      34
#define CAM_PIN_D5      39
#define CAM_PIN_D4      36
#define CAM_PIN_D3      21
#define CAM_PIN_D2      19
#define CAM_PIN_D1       18
#define CAM_PIN_D0       5
#define CAM_PIN_VSYNC   25
#define CAM_PIN_HREF    23
#define CAM_PIN_PCLK    22

#define CAM_PWDN_ON false
#define CAM_PWDN_OFF true

/* Defined privately in components/esp32-camera/driver/xclk.c */
esp_err_t camera_enable_out_clock(camera_config_t *config);
void camera_disable_out_clock();

static esp_pm_lock_handle_t freq_handle = 0;


static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sscb_sda = CAM_PIN_SIOD,
    .pin_sscb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,  //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QXGA,  //QQVGA-QXGA Do not use sizes above QVGA when not JPEG

    /* Value in range 0-63 where a lower value means higher quality
     * 4 is the lowest number I can get to reliably work
     */
    .jpeg_quality = 4, //0-63 lower number means higher quality
    .fb_count = 1 //if more than one, i2s runs in continuous mode. Use only with JPEG
};

esp_err_t camera_start()
{
    esp_err_t err;

    ESP_ERROR_CHECK(esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "camera", &freq_handle));

    camera_on();
    err = esp_camera_init(&camera_config);

    camera_disable_out_clock();

    return err;
}

esp_err_t camera_on()
{
    if(camera_config.pin_pwdn >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << camera_config.pin_pwdn;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);
        gpio_set_level(camera_config.pin_pwdn, CAM_PWDN_ON);
        vTaskDelay(100/portTICK_RATE_MS);
    }

    // TODO Error Handling
    return ESP_OK;
}


esp_err_t camera_off()
{
    if(camera_config.pin_pwdn >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << camera_config.pin_pwdn;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);
        gpio_set_level(camera_config.pin_pwdn, CAM_PWDN_OFF);
        vTaskDelay(100/portTICK_RATE_MS);
    }

    // TODO Error Handling
    return ESP_OK;
}


camera_fb_t* camera_fb_get()
{
    camera_fb_t *fb;
	ESP_ERROR_CHECK(esp_pm_lock_acquire(freq_handle));
    ESP_ERROR_CHECK(camera_enable_out_clock(&camera_config));
    fb = esp_camera_fb_get();
    camera_disable_out_clock();
	ESP_ERROR_CHECK(esp_pm_lock_release(freq_handle));
    return fb;
}
