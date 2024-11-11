#define _GNU_SOURCE

#include "../include/string.h"
#include "../include/io.h"

#define RED "\x1B[31m" 
#define GREEN "\x1B[32m" 
#define YELLOW "\x1B[33m" 
#define BLUE "\x1B[34m" 
#define MAGENTA "\x1B[35m" 
#define CYAN "\x1B[36m" 
#define RESET "\x1B[0m"

#define WELCOME_MSG "\nInitializing FunkyBase...\n\n\n"
#define PROMPT "FunkyBase> "
#define EXIT_MSG "\nExiting FunkyBase\n"

#define FB_VERSION "FunkyBase v0.1"


/*
 * IDEES D'IMPLEMENTACIÓ:
 * - Per a les funcions estaria interessant tenir diversos arrays on l'index de cadaun sigui una comanda,
 * després a l'hora d'implementar missatges d'error d'us o comprovar quin és la comanda introduida es pot 
 * fer per indexos d'aquests arrays. 
 */




void parseArguments(char ** argv, int argc) {

    if (!STRING_compare(argv[0], "EXIT", CASE_INSENSITIVE)) {
        printLine(EXIT_MSG);
		exit(EXIT_SUCCESS);
    } else if (!STRING_compare(argv[0], "VERSION", CASE_INSENSITIVE)) {
        switch(argc){
            case 1:
                printColorLine(FB_VERSION, GREEN);
                break;
            case 2:
                printError("To be implemented...\n")
                break;
            default:
                printColor(STRING_toLowerCase(argv[0]), YELLOW); 
                for (int i = 1; i < argc; i++) {
                    print(" ");
                    printColor(argv[i], YELLOW); 
                }
                printError(": invalid options\n");
                printColor(STRING_toLowerCase(argv[0]), YELLOW); 
                printError(": usage: \n") //to be implemented :)
        }

    } else {
        printColor(STRING_toLowerCase(argv[0]), YELLOW);    
        printError(": unrecognized command\n");
        return;

    }


    return;
}

char** getArguments(char * string, char separator, char ending, int * argc) {
    
    int b_size = 0;
    (*argc) = 0;

    char * buffer = NULL;
    char ** argv = NULL;

    for (int i = 0; i < STRING_length(string) + 1; i++) {

        if (string[i] == separator || string[i] == ending) {
            
            if (b_size == 0 && string[i] == separator) continue;
            if (b_size == 0 && string[i] == ending) break;            

            (*argc)++;
            buffer[b_size] = '\0';
            
            argv = realloc(argv, sizeof(char*) * (*argc));
            argv[(*argc) - 1] = malloc(sizeof(char) * b_size);
            
            argv[(*argc) - 1] = STRING_copy(buffer);
            
            if (string[i] == ending) break;
            b_size = 0;
            continue;
        }

        b_size++;
        buffer = realloc(buffer, sizeof(char) * (b_size + 1));
        buffer[b_size - 1] = string[i];
    }

    free(buffer);

    return argv;
}


void freeArgs(char ** argv, int argc) {

    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }

    free(argv);
}


int main(void) {

    int argc;         
    char ** argv;     

    char * input;
    print(WELCOME_MSG);    

    
    while (1) {
        print(PROMPT);
        input = IO_readUntil(STDIN_FILENO, '\n');
        argv = getArguments(input, ' ', '\0', &argc);
        if (argc > 0) parseArguments(argv, argc);


        freeArgs(argv, argc);
        free(input);        //implement a buffer of past comands??? ^[[A^[[B^[[C^[[D (READ ^[[...)
    }

    return EXIT_SUCCESS;
}