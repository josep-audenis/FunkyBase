#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define RED "\x1B[31m" 
#define GREEN "\x1B[32m" 
#define YELLOW "\x1B[33m" 
#define BLUE "\x1B[34m" 
#define MAGENTA "\x1B[35m" 
#define CYAN "\x1B[36m" 
#define RESET "\x1B[0m"

#define WELCOME_MSG "\nInitializing FunkyBase...\n\n\n"
#define PROMPT "FunkyBase> "

#define EXIT_SUCCESS 0
#define LOW_UPP_DIF 'A'-'a'

#define print(x) write(STDOUT_FILENO, x, strlen(x));
#define printError(x) write(STDOUT_FILENO, RED, strlen(RED)); write(STDOUT_FILENO, x, strlen(x)); write(STDOUT_FILENO, RESET, strlen(RESET));
#define printColor(x, y) write(STDOUT_FILENO, y, strlen(y)); write(STDOUT_FILENO, x, strlen(x)); write(STDOUT_FILENO, RESET, strlen(RESET));



void stringCopy(char * destination, char * origin); //TODO :)
int stringLength(char * string); //TODO :)


char * readUntil(int fd, char delimitator){
    char * buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    int i = 0;
    int bytes_read;
    char aux;

    bytes_read = read(fd, &aux, sizeof(char));

    while(aux != delimitator && aux != '\n'){
        if (bytes_read == 0){
            return buffer;
        }

        i++;
        buffer = realloc(buffer, sizeof(char) * (i+1));
        buffer[i-1] = aux;

        bytes_read = read(fd, &aux, sizeof(char));
    }

    buffer[i] = '\0';

    return buffer;
}

char** getArguments(char * string, char separator, char ending, int * argc){
    
    int b_size = 0;
    (*argc) = 0;

    char * buffer = NULL;
    char ** argv = NULL;

    for (int i = 0; i < (int) strlen(string) + 1; i++) {

        if (string[i] == separator || string[i] == ending) {
            
            if (b_size == 0 && string[i] == separator) continue;
            if (b_size == 0 && string[i] == ending) break;            

            (*argc)++;
            buffer[b_size] = '\0';
            
            argv = realloc(argv, sizeof(char*) * (*argc));
            argv[(*argc) - 1] = malloc(sizeof(char) * b_size);
            
            strcpy(argv[(*argc) - 1], buffer);
            
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

void freeArgs(char ** argv, int argc){
    for (int i = 0; i < argc; i++){
        free(argv[i]);
    }
    free(argv);
}

int main(void){

    int argc;         
    char ** argv;     
    
    char * input;
    print(WELCOME_MSG);

    while (1) {
        print(PROMPT);
        input = readUntil(STDIN_FILENO, '\n');
        argv = getArguments(input, ' ', '\0', &argc);

        //comand parser :)

        freeArgs(argv, argc);
        free(input);        //implement a buffer of past comands??? ^[[A^[[B^[[C^[[D (READ ^[[...)
    }

    return EXIT_SUCCESS;
}