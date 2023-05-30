#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    unsigned int size; // Agrego un contador para la cantidad de elementos para que sea orden constante
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue));
    q->first = NULL;
    q->size = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}
queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    q->size++; // Incremento el contador de elementos
    if (q->first==NULL) {
        q->first = new_node;
    } else {
        struct s_node *p = q->first; // Agrego un puntero para recorrer la lista y llegar al final
        while(p->next != NULL){
            p = p->next; // Incremento el contador de elementos  
        }
        p->next = new_node;  // Agrego el nuevo nodo al final de la lista
    }
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    return q->size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    q->size--; 
    return q;
}
// Esta funcion elimina de la cola a la posicion n y el resto de elementos quedan en el mismo orden
queue queue_disscard(queue q, unsigned int n)  
{
    assert(invrep(q) && !queue_is_empty(q));
    if (n == 0)
    {
        queue_dequeue(q);
    }
    else
    {
        struct s_node * p = q->first;
        struct s_node * killme = NULL;
        for (unsigned int i = 0; i < n-1; i++)
        {
            p = p->next;
        }
        killme = p->next;
        p->next = p->next->next;
        killme = destroy_node(killme);
        q->size--;
    }   
    return q;
}


void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

