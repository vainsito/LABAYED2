/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last line in flight file
* @return True when is the last line of the file, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
        f.code,
        f.type == 0 ? "last_mile" : "layover",
        f.passengers_amount,
        f.hour - 1,
        f.delay
      );
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int compensation_cost (DelayTable a, unsigned int h) {
  unsigned int demoras_pormin_despegue = 0;
  unsigned int demoras_pormin_llegada= 0;
  unsigned int compensation_total = 0;
  unsigned int cant_pasajeros_demorados_despegue = 0;
  unsigned int cant_pasajeros_demorados_llegada = 0;
  for (unsigned int i = 0; i < h; i++)
  {
    if (a[0][i].delay > MAX_LM_DELAY_ALLOWED)
    {
      demoras_pormin_despegue = demoras_pormin_despegue + a[0][i].delay;
      cant_pasajeros_demorados_despegue = cant_pasajeros_demorados_despegue + a[0][i].passengers_amount; 
    }
    if (a[1][i].delay > MAX_LAYOVER_DELAY_ALLOWED)
    {
      demoras_pormin_llegada = demoras_pormin_llegada + a[1][i].delay;
      cant_pasajeros_demorados_llegada = cant_pasajeros_demorados_llegada + a[1][i].passengers_amount; 
    }
  }
  compensation_total = demoras_pormin_despegue*cant_pasajeros_demorados_despegue + demoras_pormin_llegada * cant_pasajeros_demorados_llegada;  

  return compensation_total;
}


void array_from_file(DelayTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while ((i<HOURS) && !feof(file)) {
    /* COMPLETAR: lectura de cada vuelo */

    Flight last_mile_info = flight_from_file(file);
    Flight layover_info = flight_from_file(file);
    int check = fscanf(file, " #%c#\n", &code);
    if (check != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    last_mile_info.code = code;
    last_mile_info.type = 0;
    layover_info.type = 1;
    layover_info.code = code;
    array[last_mile_info.type][last_mile_info.hour-1] = last_mile_info;
    array[layover_info.type][layover_info.hour-1] = layover_info;
  }
  fclose(file);
}
