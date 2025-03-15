#ifndef WIFI_H
#define WIFI_H

void wifi_init_nvs(void);
void wifi_init_sta(void);
void wifi_connect(const char* ssid, const char* password);
void wifi_disconnect(void);

#endif // WIFI_H
