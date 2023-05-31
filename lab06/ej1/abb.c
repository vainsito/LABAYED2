#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"
struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool inv = true;
    if(tree != NULL){
        if (tree->left != NULL)
        {
            inv = inv && elem_less(tree->left->elem,tree->elem);
        }
        if(tree->right != NULL)
        {
            inv = inv && elem_less(tree->elem,tree->right->elem);
        }       
        inv = inv &&invrep(tree->left) && invrep(tree->right);  
    }
    return inv;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (abb_is_empty(tree)) {
        abb newe = malloc(sizeof(struct _s_abb));
        newe->elem = e;
        newe->left = NULL;
        newe->right = NULL;
        return newe;  // Devuelve el nuevo nodo como la raíz del árbol
    }
    else if (elem_less(e, tree->elem)) {
        tree->left = abb_add(tree->left, e);  // Agregar el elemento al subárbol izquierdo
    }
    else if (elem_less(tree->elem, e)) {
        tree->right = abb_add(tree->right, e);  // Agregar el elemento al subárbol derecho
    }
    // No es necesario hacer nada si el elemento ya existe en el árbol

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}


bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return (tree == NULL);
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (!abb_is_empty(tree))
    {
        exists = (elem_eq(tree->elem, e) ? true : (elem_less(tree->elem, e) ? abb_exists(tree->right, e) : abb_exists(tree->left, e)));
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (!abb_is_empty(tree))
    {
     length = 1 + abb_length(tree->left) + abb_length(tree->right);   
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}
//devuelve el nodo con el valor minimo de un arbol binario

static abb minValueNode(abb tree){
    abb min_node = tree ;
    while (!abb_is_empty(min_node) && !abb_is_empty(min_node->left))
    {
        min_node = min_node->left;
    }
    return min_node;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(abb_exists(tree, e))
    {
        if (elem_less(tree->elem, e))
        {
            tree->right = abb_remove(tree->right, e);
        }
        else if (elem_less(e, tree->elem))
        {
            tree->left = abb_remove(tree->left, e);
        }
        else
        {
            if (abb_is_empty(tree->left))
            {
                abb aux = tree->right;
                free(tree);
                return aux;
            }
            else if (abb_is_empty(tree->right))
            {
                abb aux = tree->left;
                free(tree);
                return aux;
            }
            abb aux = minValueNode(tree->right);
            tree->elem = aux->elem;
            tree->right = abb_remove(tree->right, aux->elem);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    max_e = (abb_is_empty(tree->right) ? tree->elem : abb_max(tree->right));
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    min_e = (abb_is_empty(tree->left) ? tree->elem : abb_min(tree->left));
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (abb_is_empty(tree))
    {
        free(tree);
        tree = NULL;
        return tree;
    }
    tree->right = abb_destroy(tree->right);
    tree->left = abb_destroy(tree->left);
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

