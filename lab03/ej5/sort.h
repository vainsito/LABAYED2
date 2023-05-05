#ifndef _SORT_H
#define _SORT_H
#include <stdbool.h>
#include "player.h"

bool goes_before(player_t x, player_t y);

void swap(player_t atp[], unsigned int i, unsigned int j);

bool array_is_sorted(player_t atp[], unsigned int length);

unsigned int partition(player_t atp[], unsigned int izq, unsigned int der);

void sort_rec(player_t atp[], unsigned int izq, unsigned int der);

void sort(player_t atp[], unsigned int length);

#endif
