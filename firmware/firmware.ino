#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

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

// This should use the default spi pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
volatile uint32_t lastIsrAt = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

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
	Serial.print("Aniweather booting up...");

	tft.initR(INITR_BLACKTAB);
	Serial.print("Screen initialized");

	// Clear screen
	tft.fillScreen(ST77XX_BLACK);
	Serial.print("Screen cleared");

	SD.begin(SD_CS);
	Serial.print("SD card initialized");

	timerSemaphore = xSemaphoreCreateBinary();
	timer = timerBegin(1000000);
	timerAttachInterrupt(timer, &onTimer);
	timerAlarm(timer, 1000000, true, 0);
	Serial.print("Timer initialized");

	attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), lbutton, FALLING);
	attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), rbutton, FALLING);
	Serial.print("Interrupts initialized");
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
