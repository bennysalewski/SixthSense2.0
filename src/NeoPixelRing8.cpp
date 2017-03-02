#include <NeoPixelRing8.h>

NeoPixelRing8::NeoPixelRing8(uint16_t n, uint8_t p, neoPixelType t = NEO_GRB + NEO_KHZ800) {
	ring = Adafruit_NeoPixel(n, p, t);
}

NeoPixelRing8::NeoPixelRing8(Adafruit_NeoPixel ring) {
	this->ring = ring;

	this->ring.begin();
	this->ring.setBrightness(255);
}

NeoPixelRing8::~NeoPixelRing8() {}

void NeoPixelRing8::begin() {
	ring.begin();
	ring.setBrightness(255);
}

void NeoPixelRing8::setPixel(uint16_t pixel, uint8_t color[4]) {
	ring.setPixelColor(pixel, ring.Color((color[0] * (color[3] + 1)) >> 8, (color[1] * (color[3] + 1)) >> 8, (color[2] * (color[3] + 1)) >> 8));
	ring.show();
}

void NeoPixelRing8::displayFrame(uint8_t frame[8][4]) {
	for (int i = 0; i < 8; i++) {
		ring.setPixelColor(i, ring.Color((frame[i][0] * (frame[i][3] + 1)) >> 8, (frame[i][1] * (frame[i][3] + 1)) >> 8, (frame[i][2] * (frame[i][3] + 1)) >> 8));
	}

	ring.show();
}
