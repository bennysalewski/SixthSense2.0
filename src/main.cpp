#include <SixthSense.h>

SixthSense sense = SixthSense();

void setup() {
	sense.begin();
}

void loop() {
	sense.update();
}
