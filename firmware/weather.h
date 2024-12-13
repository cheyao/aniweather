#ifndef WEATHER_H
#define WEATHER_H

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SD.h>

volatile bool lpressed;
volatile bool rpressed;

class WeatherStation {
      public:
	WeatherStation();
	~WeatherStation();

      private:
	void connectWifi();
	static void rbutton();
	static void lbutton();

	Adafruit_ST7735 tft;
	time_t now;
};

#endif
