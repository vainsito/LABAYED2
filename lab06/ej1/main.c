/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);


    /*

    HAY QUE PROBAR TODAS LAS OPCIONES (1 A 7)

    */
    unsigned int num = 0u;
    while(num !=7u){
        printf("\nEscribe el numero de opcion que quieres ejecutar:\n"
        "1. Mostrar el árbol por pantalla\n"
        "2. Agregar un elemento\n"
        "3. Eliminar un elemento\n"
        "4. Chequear existencia de elemento\n"
        "5. Mostrar la longitud del árbol\n"
        "6. Mostrar raiz, máximo y mínimo del árbol\n"
        "7. Salir del programa\n");
        printf("\n");
        scanf("%u",&num);
        while (num<1u || num>7u)
        {
            printf("Por favor, escribe un numero valido\n");
            scanf("%u",&num);
        }
        if(num == 1u)
        {
            printf("Su arbol actual es: \n");
            abb_dump(tree);
            printf("\n");
        } 
        else if(num == 2u)
        {
            abb_elem new_elem;
            printf("Escribe el elemento que quieres agregar en el arbol\n");
            scanf("%d",&new_elem);
            abb_add(tree,new_elem);
        } else if(num == 3u){
            abb_elem kill_elem;
            printf("Escribe el elemento que quieres remover del arbol\n");
            scanf("%d",&kill_elem);  
            abb_remove(tree,kill_elem);          
        } 
        else if(num == 4u)
        {
            abb_elem find_elem;
            printf("Escribe el elemento que quieres revisar si existe en el arbol\n");
            scanf("%d",&find_elem);
            if(abb_exists(tree,find_elem)){
                printf("El elemento %d se encuentra en el abb\n",find_elem);
            } else {
                printf("El elemento %d no se encuentra en el abb\n",find_elem);
            }
        } 
        else if(num == 5u)
        {
            printf("El abb tiene %u elementos\n",abb_length(tree));
        } 
        else if(num == 6u)
        {
            if (!abb_is_empty(tree)) {
                printf("\n");
                printf("raiz: %d\nminimo: %d\nmaximo: %d\n", abb_root(tree),
                                                            abb_min(tree),
                                                            abb_max(tree));
            } 
            else
             {
                printf("\nÁrbol vacío\n");
            }          
        }
    }
    if (num == 7u)
    {
        printf("\nAdios!\n");
    }
    tree = abb_destroy(tree);
    return (EXIT_SUCCESS);
}
