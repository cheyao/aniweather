#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "secerets.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/api-reference/peripherals/spi_master.html
#define SD_CS 8
#define TFT_CS 10
#define TFT_RST 3
#define TFT_DC 1

#define MISO 2
#define MOSI 7
#define SCK 6

#define LEFT_BUTTON 4
#define RIGHT_BUTTON 5

#define METEO_URL "https://api.open-meteo.com/v1/forecast?latitude=43.5513&longitude=7.0127&hourly=temperature_2m&forecast_days=1&models=meteofrance_seamless"

// This should use the default spi pins
hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
volatile uint32_t lastIsrAt = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

NetworkClient client;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

uint32_t lastFetch;

void IRAM_ATTR rbutton() noexcept {
}

void IRAM_ATTR lbutton() noexcept {
}

void ARDUINO_ISR_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	lastIsrAt = millis();
	portEXIT_CRITICAL_ISR(&timerMux);

	xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void setup() {
	Serial.begin(9600);
	Serial.println("Aniweather booting up...");

	tft.initR(INITR_BLACKTAB);
	Serial.println("Screen initialized");

	// Clear screen
	tft.fillScreen(ST77XX_BLACK);
	Serial.println("Screen cleared");

	SD.begin(SD_CS);
	Serial.println("SD card initialized");

	timerSemaphore = xSemaphoreCreateBinary();
	timer = timerBegin(1000000);
	timerAttachInterrupt(timer, &onTimer);
	timerAlarm(timer, 1000000, true, 0);
	Serial.println("Timer initialized");

	attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), lbutton, FALLING);
	attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), rbutton, FALLING);
	Serial.println("Interrupts initialized");

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("Wifi initialized");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void loop() {
	if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) {
		uint32_t isrTime = 0;

		portENTER_CRITICAL(&timerMux);
		isrTime = lastIsrAt;
		portEXIT_CRITICAL(&timerMux);

		// Our time is updated
		tft.fillScreen(ST77XX_BLACK);

		// Lets try to get weather if it isn't cached
		if (isrTime - 60 * 60 > )
	}
}
