#include <CardinalDirection.h>
#include <Wire.h>
#include <LSM303.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <NeoPixelRing8.h>
#include <WeatherForecaster.h>

#ifndef SRC_SIXTHSENSE_H_
#define SRC_SIXTHSENSE_H_

class SixthSense {
	public:
		SixthSense();
		virtual ~SixthSense();

    void begin();
    void update();
	private:
    int clockPin = 4;
    int latchPin = 0;
    int dataPin = 2;

    struct MotorDirection {
    	bool front[8] = {false, false, false, false, false, true, false, false};
    	bool frontRight[8] = {false, false, false, false, false, false, false, true};
    	bool right[8] = {false, false, false, false, true, false, false, false};
    	bool backRight[8] = {false, false, true, false, false, false, false, false};
    	bool back[8] = {true, false, false, false, false, false, false, false};
    	bool backLeft[8] = {false, true, false, false, false, false, false, false};
    	bool left[8] = {false, false, false, true, false, false, false, false};
    	bool frontLeft[8] = {false, false, false, false, false, false, true, false};
    	bool none[8] = {false, false, false, false, false, false, false, false};
    } motorDirection;

    struct RingColor {
      uint8_t value[4];
    } orange = {{255, 102, 0, 20}},
      blue = {{0, 153, 255, 20}},
      white = {{255, 255, 255, 20}},
      black = {{0, 0, 0, 20}};

    struct NeoPixelRing8Directions {
      bool top[8] = {false, false, false, false, true, false, false, false};
      bool topRight[8] = {false, false, false, false, false, true, false, false};
      bool right[8] = {false, false, false, false, false, false, true, false};
      bool bottomRight[8] = {false, false, false, false, false, false, false, true};
      bool bottom[8] = {true, false, false, false, false, false, false, false};
      bool bottomLeft[8] = {false, true, false, false, false, false, false, false};
      bool left[8] = {false, false, true, false, false, false, false, false};
      bool topLeft[8] = {false, false, false, true, false, false, false, false};
      bool all[8] = {false, false, false, false, false, false, false, false};
    } neoPixelRing8Directions;

    uint8_t ringColor[4] = {};
    int counter = 0;

    LSM303 compass;
    NeoPixelRing8 ring = NeoPixelRing8(8, 14, NEO_GRB + NEO_KHZ800);
    Adafruit_BMP085_Unified barometer = Adafruit_BMP085_Unified(10085);
    WeatherForecaster forecaster = WeatherForecaster();

    void setMotor(bool bits[8]);
    void setLED(bool bits[8]);
    void processDirection(CardinalDirection direction);
    void startupAnimation();
};

#endif
