/* OTA example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "string.h"

#include "nvs.h"
#include "nvs_flash.h"
#include <sys/socket.h>
#include "/Users/mwesigwaguma/Desktop/repos/Projects/EmbeddedProjects/esp32/src/common/wifi.h"

const char* ca_cert = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDrzCCApegAwIBAgIUQ0ZLE2pt2MqP3/bRUatY4jBqq/gwDQYJKoZIhvcNAQEL\n"
"BQAwZzELMAkGA1UEBhMCVVMxCzAJBgNVBAgMAkdBMRAwDgYDVQQHDAdBdGxhbnRh\n"
"MRUwEwYDVQQKDAxndW1hZW1iZWRkZWQxDTALBgNVBAsMBGd1bWExEzARBgNVBAMM\n"
"CjEwLjAuMC4yNTAwHhcNMjUwMzA0MjE1NDIxWhcNMjYwMzA0MjE1NDIxWjBnMQsw\n"
"CQYDVQQGEwJVUzELMAkGA1UECAwCR0ExEDAOBgNVBAcMB0F0bGFudGExFTATBgNV\n"
"BAoMDGd1bWFlbWJlZGRlZDENMAsGA1UECwwEZ3VtYTETMBEGA1UEAwwKMTAuMC4w\n"
"LjI1MDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALfNcBw2f1JAThRg\n"
"Y3x+zsUBo/poeNNPmMmrdPgEzWcG6LlcltPZbOUg0mvjCFoF2bwMIg5936HoVs5W\n"
"z3fm3DqyWMVODmNDP3cVULQOrm4Hb34E5MbNGsrE23hi9rYoS5zLJa7Bf5vtSIHx\n"
"32POrTFToMeekwouIdlQZVDsC5BmtHFvdUQL9/8NUVblt/DyV+NDWJw04ylpdV4q\n"
"cYXB5czrfPmjNzhMIpKy3hQHAXwaLuZBWNaEK31mRURGjcVhVdygAxeNOOCUHNCS\n"
"UFB1EPcIy+mazpNTCBmRdx4ulgjJzAeJkAzc455qNisrsT+/QL1Rq6a5z6VO1OIh\n"
"FjGt2bUCAwEAAaNTMFEwHQYDVR0OBBYEFHZWJG8ahJ1CeSLnWzn6wJW5C4NyMB8G\n"
"A1UdIwQYMBaAFHZWJG8ahJ1CeSLnWzn6wJW5C4NyMA8GA1UdEwEB/wQFMAMBAf8w\n"
"DQYJKoZIhvcNAQELBQADggEBAJZn2d5DsAUxIaMzu0568/cpeXbCSzBVPRSAAUSH\n"
"ioUrWDhcpSqZOnpX+qldP8wtAzP+7U3cazi9MnsLoi1LoQih+tHrCGML8zYJqG7C\n"
"BwXR5ru8JAAoIsZuJGkYvG3BnBKPxbILUSBtzVrvYpFAOowdv0l8EO58/t20YS/z\n"
"odxk51rhAv5AjCMAVjGLDs3t+sFaOOkoXy/xdsytz1nKSXjrVZ6uNjEPA05i3Trf\n"
"0dYn28H5kWAl0xV57g3ehhA+B4OzxnGwzLcChpkX+ONB70v+ylZMNY9poKkEDzw2\n"
"txLY1v6NPNKgKr5/X5ftkal+qvwPb9T2dOgkfULpafas9FA=\n"
"-----END CERTIFICATE-----\n";

#define URL "https://10.0.0.250:8070/httpserver.bin"

#define HASH_LEN 32

static const char *TAG = "simple_ota";

#define OTA_URL_SIZE 256

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
        break;
    }
    return ESP_OK;
}

void ota_task(void *pvParameter)
{
    ESP_LOGI(TAG, "Starting OTA task");

    esp_http_client_config_t config = {
        .url = URL,
        .cert_pem = ca_cert,
        .event_handler = _http_event_handler,
        .keep_alive_enable = true,
    };

    config.skip_cert_common_name_check = true;

    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };
    ESP_LOGI(TAG, "Attempting to download update from %s", config.url);
    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA Succeed, Rebooting...");
        esp_restart();
    } else {
        ESP_LOGE(TAG, "Firmware upgrade failed");
    }
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void print_sha256(const uint8_t *image_hash, const char *label)
{
    char hash_print[HASH_LEN * 2 + 1];
    hash_print[HASH_LEN * 2] = 0;
    for (int i = 0; i < HASH_LEN; ++i) {
        sprintf(&hash_print[i * 2], "%02x", image_hash[i]);
    }
    ESP_LOGI(TAG, "%s %s", label, hash_print);
}

static void get_sha256_of_partitions(void)
{
    uint8_t sha_256[HASH_LEN] = { 0 };
    esp_partition_t partition;

    // get sha256 digest for bootloader
    partition.address   = ESP_BOOTLOADER_OFFSET;
    partition.size      = ESP_PARTITION_TABLE_OFFSET;
    partition.type      = ESP_PARTITION_TYPE_APP;
    esp_partition_get_sha256(&partition, sha_256);
    print_sha256(sha_256, "SHA-256 for bootloader: ");

    // get sha256 digest for running partition
    esp_partition_get_sha256(esp_ota_get_running_partition(), sha_256);
    print_sha256(sha_256, "SHA-256 for current firmware: ");
}

void app_main(void)
{
    ESP_LOGI(TAG, "OTA app_main start");

    // Initialize NVS.
    wifi_init_nvs();

    get_sha256_of_partitions();

    /* This helper function configures Wi-Fi.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    wifi_connect();

    /* Ensure to disable any WiFi power save mode, this allows best throughput
     * and hence timings for overall OTA operation.
     */
    esp_wifi_set_ps(WIFI_PS_NONE);

    xTaskCreate(&ota_task, "ota_task", 8192, NULL, 5, NULL);
}