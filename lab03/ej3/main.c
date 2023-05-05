#include <stdlib.h>
#include <stdio.h>
#include "array_helper.h"

#define MAX_SIZE 1000

unsigned int
data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){

    FILE *fichero;
    fichero = fopen(path, "rt");

    unsigned int largo = 0;

    for(unsigned int i = 0; !feof(fichero); i++){
        fscanf(fichero,"%u -> *%c*\n",&indexes[largo],&letters[largo]);
        largo++;
    }

    fclose(fichero);

    if (largo > max_size){
        return max_size;
    } else {
        return largo;
    }
    
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    //argc = Cantidad de argumentos que se ingresan al compilar
    //argv = Los argumentos que ingresaste al compilar 
    FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];

    unsigned int length = 0; 
    unsigned int j = 0;

    char *path = NULL;
    path = parse_filepath(argc,argv);  

    file = fopen(path, "rt");

    length = data_from_file(argv[1],indexes,letters,MAX_SIZE); //argv[1] es la localizacion del imput el argv[0] es el que compila

    fclose(file);

    if (argc < 2){
        printf("Error \n");
        exit(EXIT_FAILURE);
    }

    for(unsigned int i = 0; i < length ; i++){
        j = 0;
        while (indexes[j] != i){   
           if (MAX_SIZE < indexes[j]){
            printf("Error in index \n");
            exit(EXIT_FAILURE);
           } else {
            j++;    
           }           
           sorted[i] = letters[j];
    }
    }

    dump(sorted, length);

    return EXIT_SUCCESS;
}

