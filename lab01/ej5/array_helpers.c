/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mybool.h"
#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {

    FILE *fichero = fopen(filepath,"rt");

    if (fichero == NULL){
        printf("Error in open file\n");
        exit(EXIT_FAILURE);
    }

    unsigned int size;
    fscanf(fichero,"%u",&size); 

    if(size>max_size){
        printf("Error in size format\n");
        exit(EXIT_FAILURE);
    }

    for(unsigned int i=0 ; i<size; i++){
        fscanf(fichero,"%d",&array[i]);
        if ( i == size - 1 && (feof(fichero))){
            printf("Error in file format\n");
            exit(EXIT_FAILURE);
        
    }}

    fclose(fichero);

    return size;
}

void array_dump(int a[], unsigned int length){
    
    printf("[");
    for(unsigned int i = 0; i<length ; i++){
        printf(" %d",a[i]);
        if(i<length - 1){
            printf(",");
        }
    }
    
    printf("]\n");
}


mybool array_is_sorted(int a[], unsigned int length){

    mybool ordenado = true;

    for (unsigned int i= 0 ; i<length-1; i++){
        ordenado = ordenado && a[i]<a[i+1];
    }

    return ordenado;
}





