#ifndef WEATHER_UTILS_H_
#define WEATHER_UTILS_H_


#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "weather.h"

int minTemPH (WeatherTable a);

void procedimiento(WeatherTable a, int output[YEARS]);

void procedimiento2(WeatherTable a, month_t output[YEARS]);


#endif