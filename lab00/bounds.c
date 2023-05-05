#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res = {true,true,false,0};
    unsigned int i = 0;
    while (i < length) {
        if (arr[i] < value){
            res.is_upperbound = true && res.is_upperbound;
            res.is_lowerbound = false;
        } else if (arr[i] > value){
            res.is_lowerbound = true && res.is_lowerbound;
            res.is_upperbound = false;
        }
        if (value == arr[i]){
            res.exists = true;
            res.where = i;
        }
        i++;
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE];
    int value, i=0;

    while (i < ARRAY_SIZE){
      printf("Otorgue un valor al indice %d\n",i);
      scanf("%d",&a[i]);
      i++;
    }
    printf("Ingrese el valor a comparar\n");
    scanf("%d",&value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    if (result.is_upperbound){
      printf("El valor ingresado es una cota superior del arreglo\n");
    }
    if (result.is_lowerbound){
      printf("El valor ingresado es una cota inferior del arreglo\n");
    }
    if (result.is_upperbound && result.exists) {
      printf("El valor ingresado es el maximo del arreglo y se encuentra en la posicion %d\n",result.where);
    }
    if (result.is_lowerbound && result.exists) {
      printf("El valor ingresado es el minimo del arreglo y se encuentra en la posicion %d\n",result.where);
    }
    if (result.is_lowerbound == false && result.is_upperbound == false){
        printf("El valor ingresado no se comporta como cota, ni como maximo o minimo\n");
    }
    return EXIT_SUCCESS;
}

