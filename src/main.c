#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "FunkyBase > "

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#define print(x) write(STDOUT_FILENO, x, strlen(x));



int main(){

    while (1) {
        print(PROMPT);
    }

    return EXIT_SUCCESS;
}