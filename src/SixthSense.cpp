#include <SixthSense.h>

SixthSense::SixthSense() {};

SixthSense::~SixthSense() {};

void SixthSense::begin() {
  Wire.begin(12, 13);
  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  setMotor(motorDirection.none);

  compass.init();
  compass.enableDefault();

  Serial.println(barometer.begin());
  ring.begin();

  memcpy(ringColor, white.value, sizeof(ringColor));

  startupAnimation();
}

void SixthSense::update() {
  float headingDegrees = 0;
  sensors_event_t event;

  compass.read();
  barometer.getEvent(&event);

  if (event.pressure && counter >= 36000) {
    forecaster.addValue(event.pressure);

    WeatherForecast forecast = forecaster.getForecast();

    switch(forecast) {
      case Anticyclone:
        memcpy(ringColor, orange.value, sizeof(ringColor));

        break;
      case Cyclone:
        memcpy(ringColor, blue.value, sizeof(ringColor));

        break;
    }

    counter = 0;
  }

  if ((compass.a.x > 0 && compass.a.x < 10000) || (compass.a.x < 0 && compass.a.x > -10000)) {
    headingDegrees = compass.heading((LSM303::vector<int>){1, 0, 0});
  } else {
    headingDegrees = compass.heading((LSM303::vector<int>){0, 0, 1});
  }

  if ((headingDegrees >= 338 && headingDegrees <= 360) || (headingDegrees >= 0 && headingDegrees <= 22)) {
    processDirection(South);
  } else if (headingDegrees >= 23 && headingDegrees <= 67) {
    processDirection(SouthWest);
  } else if (headingDegrees >= 68 && headingDegrees <= 112) {
    processDirection(West);
  } else if (headingDegrees >= 113 && headingDegrees <= 137) {
    processDirection(NorthWest);
  } else if (headingDegrees >= 138 && headingDegrees <= 202) {
    processDirection(North);
  } else if (headingDegrees >= 203 && headingDegrees <= 247) {
    processDirection(NorthEast);
  } else if (headingDegrees >= 248 && headingDegrees <= 292) {
    processDirection(East);
  } else if (headingDegrees >= 293 && headingDegrees <= 337) {
    processDirection(SouthEast);
  }

  counter++;

  delay(100);
}

void SixthSense::setMotor(bool bits[8]) {
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, bits[i]);
    digitalWrite(clockPin, LOW);
  }

  digitalWrite(latchPin, HIGH);
}

void SixthSense::setLED(bool bits[8]) {
  uint8_t frame[8][4] = {};

  for (int i = 0; i < 8; i++) {
    if (bits[i]) {
      memcpy(frame[i], black.value, sizeof(frame[i]));
    } else {
      memcpy(frame[i], ringColor, sizeof(frame[i]));
    }
  }

  ring.displayFrame(frame);
}

void SixthSense::startupAnimation() {
  uint8_t frames[8][8][4] = {{{255, 255, 255, 20},{0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {0, 0, 0, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {0, 0, 0, 20}},
                         {{255, 255, 255, 20},{255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}, {255, 255, 255, 20}}};

  for (int i = 0; i < 8; i++) {
    ring.displayFrame(frames[i]);

    delay(200);
  }
}

void SixthSense::processDirection(CardinalDirection direction) {
  if ((compass.a.x > 0 && compass.a.x < 10000) || (compass.a.x < 0 && compass.a.x > -10000)) {
    setMotor(motorDirection.none);

    switch(direction) {
      case North:
        setLED(neoPixelRing8Directions.top);

        break;
      case NorthEast:
        setLED(neoPixelRing8Directions.topLeft);

        break;
      case East:
        setLED(neoPixelRing8Directions.left);

        break;
      case SouthEast:
        setLED(neoPixelRing8Directions.bottomLeft);

        break;
      case South:
        setLED(neoPixelRing8Directions.bottom);

        break;
      case SouthWest:
        setLED(neoPixelRing8Directions.bottomRight);

        break;
      case West:
        setLED(neoPixelRing8Directions.right);

        break;
      case NorthWest:
        setLED(neoPixelRing8Directions.topRight);

        break;
    }
  } else {
    setLED(neoPixelRing8Directions.all);

    switch(direction) {
      case North:
        setMotor(motorDirection.front);

        break;
      case NorthEast:
        setMotor(motorDirection.frontLeft);

        break;
      case East:
        setMotor(motorDirection.left);

        break;
      case SouthEast:
        setMotor(motorDirection.backLeft);

        break;
      case South:
        setMotor(motorDirection.back);

        break;
      case SouthWest:
        setMotor(motorDirection.backRight);

        break;
      case West:
        setMotor(motorDirection.right);

        break;
      case NorthWest:
        setMotor(motorDirection.frontRight);

        break;
    }
  }
}
