#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>
/*Definicion de el TAD STACK */

struct _s_stack
{
    stack_elem elem;
    struct _s_stack *next; 
};


/*Definicion de las funciones del TAD STACK*/

stack stack_empty(void)
{
    stack s = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e)
{
    stack q;
    q = malloc(sizeof(stack));
    q->elem = e;
    q->next = s;
    s = q;
    return s;
}

stack stack_pop(stack s)
{
	if (s != NULL) {
		stack g = s;
		s = s->next;
		free(g);
	}
	return s;
}

unsigned int stack_size(stack s)
{
    stack p = s;
    unsigned int size = 0;
    while (p != NULL)
    {
        size++;
        p = p->next;
    }
    return size;
}

stack_elem stack_top(stack s)
{
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s)
{
    return (s == NULL);
}

stack_elem *stack_to_array(stack s)
{
    unsigned int size = stack_size(s);
    stack_elem *array = calloc(size, sizeof(stack_elem));  // Reservamos memoria para el array, multiplicamos por size ya que es el numero de elementos que tiene la pila
    if (!stack_is_empty(s))
    {
        for (unsigned int i = size; i > 0; i--)
        {
            array[i-1] = stack_top(s);  // Asignamos el valor de p->elem a la posicion i del array
            s = stack_pop(s);               // Eliminamos el elemento de la pila      
        }
    }
    else
    {
        array = NULL;
    }
    return array;
}

stack stack_destroy(stack s)
{
    stack p;
    stack q;
    p = s;
    while (p->next != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(p);
    return s;    
}
