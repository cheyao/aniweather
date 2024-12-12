#include "weather.h"

#define METEO_URL "https://api.open-meteo.com/v1/forecast?latitude=43.5513&longitude=7.0127&hourly=temperature_2m&forecast_days=1&models=meteofrance_seamless"
// Daily waifus!
#define WAIFU_URL "https://api.waifu.im/search"
#define WIFI_HOSTNAME "Aniweather"

WeatherStation::WeatherStation() : tft(Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST)) {
	tft.initR(INITR_BLACKTAB);
	tft.fillScreen(ST77XX_BLACK);
	Serial.println("Screen initialized");

	SD.begin(SD_CS);
	Serial.println("SD card initialized");

	connectWifi();
}

WeatherStation::~WeatherStation() {
	// Cleanup!
}

void WeatherStation::connectWifi() {
	Serial.println("Connecting to WiFi");
	if (WiFi.status() == WL_CONNECTED) {
		return;
	}

	WiFi.disconnect();
	WiFi.mode(WIFI_MODE_NULL);
	WiFi.hostname(WIFI_HOSTNAME);
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	int progress = 0;
	
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	
		if (progress > 80) {
			progress = 0;
		}
		progress += 10;

		// TODO: Draw the progress

		Serial.print(".");
	}

	Serial.println("WiFi connected");
	Serial.printf("IP address: %s/%s\n", WiFi.localIP().toString().c_str(), WiFi.subnetMask().toString().c_str());
	Serial.printf("MAC address: %s/%s\n", WiFi.macAddress().c_str());
}

