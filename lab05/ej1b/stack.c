#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>
/*Definicion de el TAD STACK */

struct node {
  stack_elem elem;
  struct node *next;
}; 

struct _s_stack
{
  struct node *first;
  unsigned int size;
};

/*Definicion de las funciones del TAD STACK*/

stack stack_empty(void)
{
    stack s=NULL;
    s = malloc(sizeof(struct _s_stack));
    s->first = NULL;
    s->size = 0;
    return s;
}

stack stack_push(stack s, stack_elem e)
{
    struct node *q;
    q = malloc(sizeof(struct node));
    q->elem = e;
    q->next = s->first;
    s->first = q;
    s->size +=1;
    return s;
}

stack stack_pop(stack s)
{
	if (s != NULL) {
		struct node  *g = s->first;
		s->first = g->next;
        s->size -=1;
		free(g);
	}
	return s;
}

unsigned int stack_size(stack s)
{
    return s->size;
}

stack_elem stack_top(stack s)
{
    assert(s != NULL);
    struct node *p = s->first;
    return p->elem;
}

bool stack_is_empty(stack s)
{
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s)
{
    unsigned int size = stack_size(s);
    stack_elem *array = calloc(size, sizeof(stack_elem)); // Reservamos memoria para el array, multiplicamos por size ya que es el numero de elementos que tiene la pila
    if (!stack_is_empty(s))
    {
        for (unsigned int i = size; i > 0; i--)
        {
            array[i-1] = stack_top(s);          // Guardamos el elemento de la pila en el array
            s = stack_pop(s);               // Eliminamos el elemento de la pila        
        }
    }
    else
    {

        array = NULL;
        printf("La pila esta vacia, entonces tu arreglo es nulo\n");
    }
    return array;
}

stack stack_destroy(stack s)
{
    struct node *q;
    struct node *p = s->first;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(p);
    return s;    
}
