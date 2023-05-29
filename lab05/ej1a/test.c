#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int main(){
    stack pila1 = stack_empty();
    stack pila2 = stack_empty();
    printf("A1=%d\n", stack_is_empty(pila1));
    pila1 = stack_push(pila1,0);
    printf("A2=%d\n", stack_is_empty(pila1));
    pila1 = stack_pop(pila1);
    printf("A3=%d\n\n", stack_is_empty(pila1));


    pila1 = stack_push(pila1, 2);
    printf("B1=%d\n",stack_is_empty(pila1));
    printf("B2=%d\n",stack_size(pila1));
    printf("B3=%d\n\n",stack_top(pila1));
    pila1 = stack_push(pila1, 8);
    printf("c1=%d\n",stack_is_empty(pila1));
    printf("c2=%d\n",stack_size(pila1));
    printf("c3=%d\n\n",stack_top(pila1));
    pila1 = stack_push(pila1, 16);
    printf("D1=%d\n",stack_is_empty(pila1));
    printf("D2=%d\n",stack_size(pila1));
    printf("D3=%d\n\n",stack_top(pila1));

    pila1 = stack_pop(pila1);
    printf("E1=%d\n",stack_is_empty(pila1));
    printf("E2=%d\n",stack_size(pila1));
    printf("E3=%d\n\n",stack_top(pila1));
    pila1 = stack_push(pila1, 9);
    printf("F1=%d\n",stack_is_empty(pila1));
    printf("F2=%d\n",stack_size(pila1));
    printf("F3=%d\n\n",stack_top(pila1));


    stack_elem *p = stack_to_array(pila1);
    stack_elem *q = stack_to_array(pila2);
    printf("G1=%d\n", stack_size(pila2));
    printf("G2=%d\n", q[1]);
    printf("H1=%d\n",p[2]);
    printf("H2=%d\n",p[1]);
    printf("H3=%d\n",p[0]);
    stack_destroy(pila1);
    stack_destroy(pila2);
    free(p);
    free(q);


    return (EXIT_SUCCESS);
}