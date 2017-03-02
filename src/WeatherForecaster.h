#include <WeatherForecast.h>

#ifndef SRC_WEATHERFORECASTER_H_
#define SRC_WEATHERFORECASTER_H_

class WeatherForecaster {
	public:
		WeatherForecaster();
		virtual ~WeatherForecaster();

    void addValue(float value);
    WeatherForecast getForecast();
	private:
    float last4Values[4] = {};

    bool areEnoughValuesAvailable();
};

#endif
