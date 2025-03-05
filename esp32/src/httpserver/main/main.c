#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "secrets.h"

void app_main(void) {
    // Connect to WiFi

    while (true) {
        printf("hello world!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}