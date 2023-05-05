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

unsigned int extra_space_fee_cost (DeliveryTable a) {
  
  unsigned int resbox = 0u;
  unsigned int resletters = 0u;
  
  for(unsigned int i = 0u ; i < FEE_CLOSE_HOUR+1 ; i++){
    resbox += (a[1][i]).items_amount;
    resletters += (a[0][i]).items_amount;
  }
  
  unsigned int Totalplata = 0;
  Totalplata = ((resbox - MAX_ALLOWED_BOXES) * BOX_PENALTY) + ((resletters - MAX_ALLOWED_LETTERS)* LETTER_PENALTY);  
  return Totalplata;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (i < 24 && !feof(file)){
    int res = fscanf(file,"_%c_",&code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    Flight flight_boxes = flight_from_file(file,code,0); //le asigno a mi variable flight_boxes un vuelo que consigo de mi fichero asociado al tipo 0 por que ese denota las boxes
    array[0][flight_boxes.hour-1] = flight_boxes; 
    Flight flight_letters = flight_from_file(file,code,1); //le asigno a mi variable flight_letters un vuelo que consigo de mi fichero asociado al tipo 0 por que se denota las letters
    array[1][flight_letters.hour-1] = flight_letters; 

    i++;
  }
}
