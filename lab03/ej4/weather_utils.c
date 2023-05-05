
#include <stdio.h>
#include <stdlib.h>

#include "weather_utils.h"

int minTemPH (WeatherTable a){
int minTemp;
minTemp = INT_MAX;
for(unsigned int year = 0u; year < YEARS ; year++ ){
    for(unsigned int month = 0u ; month < MONTHS ; month++){
        for(unsigned int day = 0u ; day < DAYS ; day++){
            if (a[year][month][day]._min_temp < minTemp){
                minTemp = a[year][month][day]._min_temp;
            } 
        }
    }
}
return minTemp;
}

void procedimiento(WeatherTable a, int output[YEARS]) {
int maxTemp;
for (unsigned int year = 0; year < YEARS; year++) {
    maxTemp = INT_MIN;
    for (unsigned int month = 0; month < MONTHS ; month++){
        for(unsigned int day = 0; day < DAYS ; day++){
           if (maxTemp < a[year][month][day]._max_temp){
            maxTemp = a[year][month][day]._max_temp;
           }
        }
    }
    output[year] = maxTemp;
}
}

void procedimiento2(WeatherTable a, month_t output[YEARS]){

unsigned int highrainfallcomp;
unsigned int TotalRainFall;
month_t highrainfallmes; //para guardar el mes con mas prec en ese año 

for (unsigned int year = 0; year < YEARS; year++){
    highrainfallcomp = 0; //Como es el mes con mas precipitaciones en un año cuando llega aca tenemos que reiniciarlo
    highrainfallmes = january; 
    for (unsigned int month = 0; month < MONTHS ; month++){
        TotalRainFall = 0;
        for(unsigned int day = 0; day < DAYS ; day++){
           TotalRainFall = TotalRainFall + a[year][month][day]._rainfall; //cantidad total de precipitaciones del mes 
        }
        if (highrainfallcomp < TotalRainFall){
            highrainfallmes = month; //guarda el mes con mayor cantidad de precipitaciones 
        }
    } 
output[year] = highrainfallmes; //muestra cual fue el mes con maxima precipitacion en el año 
}
}




