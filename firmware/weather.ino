#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SD.h>

#include "weather.h"
#include "settings.h"

WeatherStation::WeatherStation() : tft(Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST)) {
	tft.initR(INITR_BLACKTAB);
	tft.fillScreen(ST77XX_BLACK);
	Serial.println("Screen initialized");

	SD.begin(SD_CS);
	Serial.println("SD card initialized");

	connectWifi();

	// This must be after then WiFi is set up
	Serial.print("Updating time");
	configTime(GMT_OFFSET, DAYLIGHT_OFFSET, NTP_SERVERS);

	// We must wait till the time is correct
	while ((now = time(nullptr)) < NTP_MIN_VALID_EPOCH) {
		Serial.print(".");
		delay(300);
		yield();
	}
	Serial.println("Time configured");

	Serial.printf("Local time: %s", asctime(localtime(&now)));
	Serial.printf("UTC time:   %s", asctime(gmtime(&now)));

	attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), rbutton, FALLING);
	attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), lbutton, FALLING);
	Serial.println("Interrupts initialized");
}

WeatherStation::~WeatherStation() {
	// Cleanup! (Nothing to do lol)
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
	Serial.printf("MAC address: %s\n", WiFi.macAddress().c_str());
}

static void WeatherStation::rbutton() {
	rpressed = true;
}

static void WeatherStation::lbutton() {
	lpressed = true;
}

