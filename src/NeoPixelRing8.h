#include <Adafruit_NeoPixel.h>

#ifndef SRC_NEOPIXELRING8_H_
#define SRC_NEOPIXELRING8_H_

class NeoPixelRing8 {
	public:
		NeoPixelRing8(uint16_t n, uint8_t p, neoPixelType t);
		NeoPixelRing8(Adafruit_NeoPixel ring);
		virtual ~NeoPixelRing8();

		void begin();
		void displayFrame(uint8_t frame[8][4]);
		void setPixel(uint16_t pixel, uint8_t color[4]);
	private:
		Adafruit_NeoPixel ring;
};

#endif
