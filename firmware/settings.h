#ifndef SETTINGS_H
#define SETTINGS_H

#include "secerets.h"

#if !defined(WIFI_SSID) || !defined(WIFI_PASSWORD)
static_assert(false, "Please create a file called secerects.h and define WIFI_SSID and WIFI_PASSWORD!");
#endif

#define WIFI_HOSTNAME "Aniweather"
// In seconds
#define GMT_OFFSET 3600
#define DAYLIGHT_OFFSET 3600
#define NTP_SERVERS "pool.ntp.org"
#define NTP_MIN_VALID_EPOCH 1533081600

#define METEO_URL "https://api.open-meteo.com/v1/forecast?latitude=43.5513&longitude=7.0127&hourly=temperature_2m&forecast_days=1&models=meteofrance_seamless"
// Daily waifus!
#define WAIFU_URL "https://api.waifu.im/search"

#define SD_CS 8
#define TFT_CS 10
#define TFT_RST 3
#define TFT_DC 1

#define MISO 2
#define MOSI 7
#define SCK 6

#define LEFT_BUTTON 4
#define RIGHT_BUTTON 5

#endif
