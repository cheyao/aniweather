#include <WiFi.h>
#include <SPI.h>
#include <SD.h>

#include "secerets.h"
#include "weather.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/api-reference/peripherals/spi_master.html

#if !defined(WIFI_SSID) || !defined(WIFI_PASSWORD)
static_assert(false, "Please create a file called secerects.h and define WIFI_SSID and WIFI_PASSWORD!");
#endif

// This should use the default spi pins
hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
volatile uint32_t lastIsrAt = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

WeatherStation* station;

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
	
	station = new WeatherStation();
}

void loop() {
	if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) {
		uint32_t isrTime = 0;

		portENTER_CRITICAL(&timerMux);
		isrTime = lastIsrAt;
		portEXIT_CRITICAL(&timerMux);

		// Our time is updated
		tft.fillScreen(ST77XX_BLACK);

	}
}
