#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>
struct node {
  stack_elem elem;
  struct node *next;
}; 

struct _s_stack
{
  struct node *first;
  unsigned int size;
};

// static bool inv_repre (stack s){
//     return (s != NULL ? s->size >0 && s->elem != NULL: true);  //NO SE SI ESTA BIEN ESTA INVREP preguntar al profe
// }

stack stack_empty(){
  stack s = NULL;
  s = malloc(sizeof(struct _s_stack));
  s->first = NULL;
  s->size = 0;
  return s;
}

stack stack_push(stack s, stack_elem e){
    struct node *nn = malloc(sizeof(struct node));
    nn->elem = e;
    nn->next = s->first;
    s->first = nn;
    s->size +=1;
    return s;
}

stack stack_pop(stack s){
  assert(!stack_is_empty(s));
  struct node *p = s->first;
  s->first = p->next;
  free(p);
  s->size -=1;
  return s;
}

unsigned int stack_size(stack s){
  return s->size;
}

stack_elem stack_top(stack s){
  assert(stack_size(s)>0);
  struct node *p = s->first;
  return p->elem;
}

bool stack_is_empty(stack s){
  return s->size == 0;
}

stack_elem *stack_to_array(stack s){
  stack_elem *s_array = calloc(stack_size(s), sizeof(stack_elem));
  struct node *p = s->first;
  if (!stack_is_empty(s))
  {
    int i=0;
    while (p!=NULL)
    {
      s_array[i] = p->elem;
      p = p->next;
      i++;
    }
    
  }else{
    s_array = NULL;
  }
  
  return s_array;
}

stack stack_destroy(stack s){
  struct node *p = s->first;
  while (s->first!=NULL)
  {
    s->first = p->next;
    free(p);
    p= s->first;
  }
  
  free(s);
  s = NULL;
  return s;
}