#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int contador = 0;
    while (s[contador] != '\0'){
        contador++;
    }
return contador;    
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool iguales = true;
    unsigned int j = fstring_length(s1);
    unsigned int k = fstring_length(s2);
    if (j != k){
        iguales = false;
        return iguales;
    }
    for (unsigned int i=0; i < j ; i++){
        if (s1[i] != s2[i]){
            iguales = false;
        }
    }
return iguales;    
}

bool fstring_less_eq(fixstring s1, fixstring s2){
    bool res = true;                                  
    unsigned int i = 0;
    unsigned int lenght1 = fstring_length(s1);
    unsigned int lenght2 = fstring_length(s2);
    if (fstring_eq(s1,s2) == true){
        return res;
    } 
    while (i < lenght1 || i < lenght2){
        if (s1[i] == s2[i]){
            i++;
        } else if (s1[i] > s2[i]){
            res = false;
            return res;
        } else if (s1[i] < s2[i]){
            res = true;
            return res;
        }
    }
return res;
}
