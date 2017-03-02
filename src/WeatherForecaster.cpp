#include <WeatherForecaster.h>

WeatherForecaster::WeatherForecaster() {}
WeatherForecaster::~WeatherForecaster() {}

void WeatherForecaster::addValue(float value) {
  for (int i = 0; i < 4; i++) {
    if (i - 1 > -1) {
      last4Values[i - 1] = last4Values[i];
    }
  }

  last4Values[3] = value;
}

WeatherForecast WeatherForecaster::getForecast() {
  float differences[3] = {};
  float avg = 0;
  int pointer = 0;

  if (areEnoughValuesAvailable()) {
    for (int i = 0; i < 4; i++) {
      if (i + 1 < 4) {
        differences[pointer] = last4Values[i + 1] - last4Values[i];

        pointer++;
      }
    }

    for (int i = 0; i < 3; i++) {
      avg += differences[i];
    }

    avg = avg / 3;

    if (avg >= 1) {
      return Anticyclone;
    } else if (avg <= -1) {
      return Cyclone;
    } else {
      return Unclear;
    }
  } else {
    return Unclear;
  }
}

bool WeatherForecaster::areEnoughValuesAvailable() {
  for (int i = 0; i < 4; i++) {
    if (last4Values[i] == 0) {
      return false;
    }
  }

  return true;
}
