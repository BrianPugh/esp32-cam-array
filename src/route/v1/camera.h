#ifndef PROJECT_CAMERA_H__
#define PROJECT_CAMERA_H__

#include "route.h"


/**
 * @brief Captures a photo
 */
esp_err_t camera_get_handler(httpd_req_t *req);

#endif
