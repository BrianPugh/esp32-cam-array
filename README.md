Firmware for forming a camera array out of multiple ESP32-CAM

# esp32-cam-array

# Usage

First define the wifi network to connnect to via the configuration manager:

```
idf.py menuconfig
```

Configuration options are available under:

```
esp32-cam-array Configuration
```

Most notable, the options:

```
esp32-cam-array Configuration>WiFi SSID
esp32-cam-array Configuration>WiFi Password
```

Warning: these values will be contained in the built binary; be careful
of distributing firmware with baked-in secrets.



<sub><sup>This project was templated from [cookiecutter-esp32-webserver](https://github.com/BrianPugh/cookiecutter-esp32-webserver)</sup></sub>
