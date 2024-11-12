#define _GNU_SOURCE

#include "../include/string.h"
#include "../include/io.h"
#include "../include/shell.h"
#include "../include/message.h"

/*
 * IDEES D'IMPLEMENTACIÓ:
 * - Per a les funcions estaria interessant tenir diversos arrays on l'index de cadaun sigui una comanda,
 * després a l'hora d'implementar missatges d'error d'us o comprovar quin és la comanda introduida es pot 
 * fer per indexos d'aquests arrays. 
 */

int main(void) {

    int argc;         
    char ** argv;     

    char * input;
    print(WELCOME_MSG);    

    
    while (1) {
        print(PROMPT);
        input = IO_readUntil(STDIN_FILENO, '\n');
        argv = SHELL_getArguments(input, ' ', '\0', &argc);
        if (argc > 0) SHELL_parseArguments(argv, argc);


        SHELL_freeArgs(argv, argc);
        free(input);        //implement a buffer of past comands??? ^[[A^[[B^[[C^[[D (READ ^[[...)
    }

    return EXIT_SUCCESS;
}