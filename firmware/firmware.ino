#include <WiFi.h>
#include <SPI.h>

#include "secerets.h"
#include "weather.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/api-reference/peripherals/spi_master.html

#if !defined(WIFI_SSID) || !defined(WIFI_PASSWORD)
static_assert(false, "Please create a file called secerects.h and define WIFI_SSID and WIFI_PASSWORD!");
#endif

void setup() {
	Serial.begin(9600);
	Serial.println("Aniweather booting up...");

	// attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), lbutton, FALLING);
	// attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), rbutton, FALLING);
	// Serial.println("Interrupts initialized");
	
	station = new WeatherStation();
}

void loop() {
	if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) {
		uint32_t isrTime = 0;

		portENTER_CRITICAL(&timerMux);
		isrTime = lastIsrAt;
		portEXIT_CRITICAL(&timerMux);
	}
}
