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
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a, unsigned int h) {
  
  unsigned int resultboxes = 0u;
  unsigned int resultletters = 0u;

  for(unsigned int hours = 0u ; hours < h; hours++){
    resultboxes += (a[0][hours]).items_amount; //calculamos la cantidad de cajas que se retienen en el deposito dentro de esas horas
    resultletters += (a[1][hours]).items_amount; //calcula la cantidad de letras que se retienen en el deposito dentro de esas horas  
  }

  unsigned int dineroTotal = 0;
  dineroTotal = ((resultboxes - MAX_ALLOWED_BOXES)*BOX_PENALTY) + ((resultletters - MAX_ALLOWED_LETTERS)*LETTER_PENALTY);
   
  return dineroTotal;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int arrival_hour;
  int i = 0;
  while (!feof(file) && i < 24){

    int res = fscanf(file,"_%c_",&code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    res = fscanf(file," %u",&arrival_hour);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    Flight flight_boxes = flight_from_file(file,code,arrival_hour);
    array[0][arrival_hour-1] = flight_boxes;

    Flight flight_letters = flight_from_file(file,code,arrival_hour);
    array[1][arrival_hour-1] = flight_letters;
    i++;
  }
  fclose(file);
}