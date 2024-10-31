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
#define PROMPT "FunkyBase > "

#define EXIT_SUCCESS 0

#define print(x, y) write(STDOUT_FILENO, y, strlen(y)); write(STDOUT_FILENO, x, strlen(x)); write(STDOUT_FILENO, RESET, strlen(RESET));



char * readUntil(int fd, char delimitator){
    char * buffer = NULL;
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



int main(int argc, char * argv[]){

    
    char * input;
    print(WELCOME_MSG, RESET);

    while (1) {
        print(PROMPT, RESET);
        input = readUntil(STDIN_FILENO, '\n');
        print(input, GREEN);
        free(input);

        print(PROMPT, RESET);
    }

    return EXIT_SUCCESS;
}