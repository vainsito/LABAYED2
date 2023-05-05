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

unsigned int TotalMinLM = 0u;
unsigned int TotalMinLAY = 0u;
unsigned int costoLAY = 0u;
unsigned int costoLM = 0u;

for(unsigned int hours = 0u; hours < h ; hours++){
    
    TotalMinLM += (a[0][hours]).delay;
    TotalMinLAY += (a[1][hours]).delay;

    if(MAX_LAYOVER_DELAY_ALLOWED < TotalMinLAY){
      costoLAY  = (TotalMinLAY - MAX_LAYOVER_DELAY_ALLOWED);
      costoLAY = (TotalMinLAY - MAX_LAYOVER_DELAY_ALLOWED)*COMPENSATION_PER_MINUTE;
      costoLAY = costoLAY * ((a[1][hours]).passengers_amount);
    }
    if (MAX_LM_DELAY_ALLOWED  < TotalMinLM){
      costoLM  = (TotalMinLM - MAX_LM_DELAY_ALLOWED);
      costoLM = (TotalMinLM - MAX_LM_DELAY_ALLOWED)*COMPENSATION_PER_MINUTE;
      costoLM = costoLM * ((a[0][hours]).passengers_amount);
    }
  } 

unsigned int resultado = costoLAY + costoLM;

return resultado;
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

  while(!feof(file) && i < HOURS) {
    
    Flight last_mile_info = flight_from_file(file);
    Flight layover_info = flight_from_file(file);

    int res = fscanf(file,"#%c#\n",&code);
    if (res != 1){
      fprintf(stderr,"Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    last_mile_info.code = code;
    last_mile_info.type = 0;
    array[last_mile_info.type][last_mile_info.hour-1] = last_mile_info;

    layover_info.code = code; //las cosas que no escaneamos en el info flight se las asignamos en otro sitio 
    layover_info.type = 1;  //en este caso no tenia en cuenta ni el codigo ni el tipo, entonces lo que hacemos es ingresarlo nosotros mismos
    array[layover_info.type][layover_info.hour-1] = layover_info;

    i++;
  }
  fclose(file);
}

