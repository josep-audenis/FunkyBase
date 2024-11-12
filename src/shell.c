#include "../include/shell.h"
#include "../include/string.h"
#include "../include/io.h"
#include "../include/message.h"


void SHELL_parseArguments(char ** argv, int argc) {

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

char** SHELL_getArguments(char * string, char separator, char ending, int * argc) {
    
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


void SHELL_freeArgs(char ** argv, int argc) {

    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }

    free(argv);
}
