
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return (x.rank <= y.rank);
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t atp[], unsigned int i, unsigned int j){
    player_t playeraux = atp[i];
    atp[i] = atp[j];
    atp[j] = playeraux;
}

unsigned int partition (player_t atp[], unsigned int izq, unsigned int der){
    unsigned ppiv,i,j;
    ppiv=izq;
    i=izq+1u;
    j=der;
    while(i<=j){
        if(goes_before(atp[i],atp[ppiv])){
            i=i+1u;
        } else if(goes_before(atp[ppiv],atp[j])){
            j=j-1u;
        } else if(goes_before(atp[ppiv],atp[i]) && goes_before(atp[j],atp[ppiv])){
            swap(atp,i,j);
        }
    } 
    swap(atp,ppiv,j);
    ppiv = j;
return ppiv;
}

void sort_rec(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der > izq){
        ppiv = partition (atp,izq,der);
        if(izq < ppiv){
            sort_rec(atp,izq,ppiv-1u);
            sort_rec(atp,ppiv+1u,der);
        } else {
            sort_rec(atp,izq,ppiv);
            sort_rec(atp,ppiv+1u,der);
        }
    }
}

void sort(player_t atp[], unsigned int length) {
    sort_rec(atp, 0u, (length == 0u) ? 0u : length - 1u);
    assert(array_is_sorted(atp, length));
}


