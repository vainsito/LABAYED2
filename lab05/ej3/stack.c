#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool inv_rep (stack s){
    return (s != NULL ? ((s->size <= s->capacity) && (s->elems != NULL) && (s->capacity >0)) : true);
}

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));      
    s->elems = malloc(sizeof(stack_elem));        
    s -> size = 0u;                                
    s->capacity = 1u;

    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(inv_rep(s));
    s->size++;
    if (s->size > s->capacity) {
        s->capacity *= 2;
        s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity);
    }
    s->elems[s->size-1] = e;
    assert(inv_rep(s));
    return s;
}

stack stack_pop(stack s)
{
    assert(inv_rep(s) && s != NULL);
        s->size -=1;
    assert(inv_rep(s) && s != NULL);
    return s;
}

unsigned int stack_size(stack s){
    assert(inv_rep(s));
    return (s == NULL ? 0u : s->size);
}

stack_elem stack_top(stack s){
    assert(inv_rep(s)&& (s != NULL));
    return s->elems[s->size -1u];
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    assert(inv_rep(s));
    stack_elem *s_array = calloc(stack_size(s), sizeof(stack_elem));
    if (!stack_is_empty(s))
    {
        for (size_t i = stack_size(s); i >0; i--)
        {
        s_array[i-1] = s->elems[i-1];
        }
    }else{
        s_array = NULL;
    }
    assert(inv_rep(s));
    return s_array;
}

stack stack_destroy(stack s)
{
   assert(inv_rep(s));
   if (s == NULL)
   {
    fprintf(stderr, "Error: stack_destroy: No se puede destruir un stack nulo\n");
    exit(EXIT_FAILURE);
   }
   free(s->elems);
   s->elems = NULL;
   free(s);
   s = NULL;
   assert(inv_rep(s));
   return s;
}