/**
*  @file strfuncs.h
*  @brief STRINGS FUNCS DEFINITIONS
*/
#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

#include <stdlib.h>


/**
* @brief calcula la lonfitud de la cadena apuntada por str
* @return la longitud de la cadena
*/
size_t string_length();

/**
* @brief devuelve una nueva cadena en memoria dinamica que se obtiene tomando los caracteres de str que son distintos del caracter c
* @param str cadena de caracteres
* @param c caracter a filtrar
* @return la nueva cadena
*/
char *string_filter(const char *str, char c);

#endif