#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *string_clone(const char *str, size_t length) {
    char *clone = NULL;  // Inicializo en NULL para que no apunte a basura
    clone = malloc((length + 1) * sizeof(char));  // Reservo memoria para el clon
    for (size_t i=0; i<length; i++) {
        clone[i] = str[i];  // Copio caracter por caracter
    }
    clone[length] = '\0';  // Agrego el caracter nulo al final
    return clone;  // Devuelvo el clon que es de tipo char* (puntero a char)
}


int main(void) {
    char original[]=""
         "______ time ago in a galaxy far, far away...\n\n\n"
         "         _______..___________.     ___      .______             \n"
         "        /       ||           |    /   \\     |   _  \\          \n"
         "       |   (----``---|  |----`   /  ^  \\    |  |_)  |          \n"
         "        \\   \\        |  |       /  /_\\  \\   |      /        \n"
         "    .----)   |       |  |      /  _____  \\  |  |\\  \\----.    \n"
         "    |_______/        |__|     /__/     \\__\\ | _| `._____|     \n"
         "                                                                \n"
         "____    __    ____      ___      .______           _______.     \n"
         "\\   \\  /  \\  /   /     /   \\     |   _  \\         /       |\n"
         " \\   \\/    \\/   /     /  ^  \\    |  |_)  |       |   (----` \n"
         "  \\            /     /  /_\\  \\   |      /         \\   \\    \n"
         "   \\    /\\    /     /  _____  \\  |  |\\  \\----..----)   |   \n"
         "    \\__/  \\__/     /__/     \\__\\ | _| `._____||_______/     \n"
         "\n\n\n"
         "                     Episode IV \n\n"
         "                     A NEW HOPE \n\n"
         "                     It is a period of civil war. Rebel\n"
         "spaceships, striking from a hidden base, have won their\n"
         "first victory against the evil Galactic Empire. During the\n"
         "battle, Rebel spies managed to steal secret plans to the\n"
         "Empire’s ultimate weapon, the DEATH STAR, an armored space\n"
         "station with enough power to destroy an entire planet.\n"
         "Pursued by the Empire’s sinister agents, Princess Leia\n"
         "races home aboard her starship, custodian of the stolen\n"
         "plans that can save her people and restore freedom to the\n"
         "galaxy...\n";
    char *copy=NULL;

    copy = string_clone(original, sizeof(original) - 1);  // Le paso la longitud del string original (sin contar el caracter nulo)
    printf("Original: %s\n", original);
    copy[0] = 'A';
    copy[1] = ' ';
    copy[2] = 'l';
    copy[3] = 'o';
    copy[4] = 'n';
    copy[5] = 'g';
    printf("Copia   : %s\n", copy);



    return EXIT_SUCCESS;
}

/*

    Los errores que encontre fueron:
    1. En la funcion string_clone se esta devolviendo un puntero a una variable local de la funcion (clone) que se destruye al salir de la funcion
    2. En la funcion string_clone no se esta reservando memoria para el string clone
    3. En la funcion main se esta pasando sizeof(original)/sizeof(char) - 1 como longitud del string original, pero esto no es correcto ya que 
    sizeof(original) devuelve el tamaño del puntero y no del string
    4. En char original, debemos pasar char original[] y no char original ya que sino no el compilador no sabe cuanta memoria reservar para el string
    y no se puede inicializar con la cadena que le pasamos.
    4. En la funcion main, al dividir sizeof(original) por sizeof(char) se esta dividiendo el tamaño del puntero por el tamaño de un char, lo cual no tiene sentido

    clone_ptr:

    Si en lugar de char original[] le ponemos char *original entonces solo estariamos creando un puntero sin asignar memoria para el string, por lo que
    al intentar inicializarlo con la cadena que le pasamos, el compilador nos va a tirar un error de segmentacion ya que no sabe cuanta memoria reservar para el string
    Y al utilizar un arreglo en la declaracion no es necesario realizar una asignacion de memoria ya que el compilador se encarga de reservar la memoria necesaria para el string   

*/