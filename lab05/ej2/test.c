#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(){
    stack s = stack_empty();;

    s = stack_push(s,1);

    printf("El elemento de S es: %d\n", stack_top(s));

    s=stack_pop(s);

    printf("El elemento de S fue eliminado\n");

    s = stack_push(s,1);

    printf("El elemento de S que se agrego es: %d\n", stack_top(s));

    s=stack_pop(s);

    stack_elem *array = stack_to_array(s);

    printf("La funcion stack_to_array de un arreglo vacio devuelve: %d\n", array[0]);
    //devuelve 0

    s = stack_push(s,1);
    s = stack_push(s,2);
    s = stack_push(s,3);
    s = stack_push(s,4);
    s = stack_push(s,5);

    array = stack_to_array(s);

    for ( unsigned int i = 0; i < 5; i++){
        printf("La funcion stack_to_array de un arreglo no vacio devuelve: %d en la posicion %u\n", array[i], i);
    }
    
    

    return(0);
}