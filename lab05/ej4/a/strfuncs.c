#include "strfuncs.h"
#include <stdio.h>

size_t string_length(const char *str)
{
    size_t i = 0;
    if (str != NULL)
    {
        while (str[i] != '\0')
        {
            i++;
        }
    }
    return i;
}

char *string_filter(const char *str, char c)
{
    size_t length = string_length(str);
    size_t filtered_length = 0;
    /*Con este for calculo la longitud nueva de la cadena*/
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != c)
        {
            filtered_length++;
        }
    }
    /*Reservo memoria para la nueva cadena*/
    char *filtered = malloc(sizeof(char) * (filtered_length + 1)); // hago un +1 para el caracter \0
    /*For para completar el arreglo*/
    size_t j = 0; //indice para la nueva cadena
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != c)
        {
            filtered[j] = str[i];
            j++;
        }
    }
    filtered[filtered_length] = '\0'; //agrego el caracter \0 en la ultima posicion
    return filtered;
}