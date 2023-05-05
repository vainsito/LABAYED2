/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

Flight flight_from_file(FILE* file, char code, unsigned int arrival_hour)
{
    Flight flight;
    flight.code = code;
    flight.hour = arrival_hour;

    int count = fscanf(file,"%u %u ",&flight.type,&flight.items_amount);
    if (count != AMOUNT_OF_FLIGHT_VARS){
      printf("Error in array\n");
      exit(EXIT_FAILURE);
    }

    return flight;
}
