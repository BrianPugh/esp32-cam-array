#ifndef PROJECT_CAMERA_H__
#define PROJECT_CAMERA_H__

#include "esp_camera.h"


/**
 *
 */
esp_err_t camera_start();


/**
 * @brief Supply power to the camera circuits.
 */
esp_err_t camera_on();


/**
 * @brief Cut off power to the camera circuits.
 *
 * Currently it ruins communication; don't use
 */
esp_err_t camera_off();


/**
 * Starts the XCLK, gets the buffer
 */
camera_fb_t* camera_fb_get();

#endif
