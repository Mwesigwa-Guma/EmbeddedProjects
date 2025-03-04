#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "secrets.h"

void app_main(void) {
    // Connect to WiFi
    wifi_connect(WIFI_SSID, WIFI_PASSWORD);

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

