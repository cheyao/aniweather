#ifndef WEATHER_H
#define WEATHER_H

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

#define SD_CS 8
#define TFT_CS 10
#define TFT_RST 3
#define TFT_DC 1

#define MISO 2
#define MOSI 7
#define SCK 6

#define LEFT_BUTTON 4
#define RIGHT_BUTTON 5

class WeatherStation {
      public:
	WeatherStation();
	~WeatherStation();

      private:
	void connectWifi();

	Adafruit_ST7735 tft;
};

#endif
