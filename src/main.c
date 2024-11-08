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
#define EXIT_MSG "\nExiting FunkyBase\n"

#define FB_VERSION "FunkyBase v0.1"

#define LOW_2_UP 'A'-'a'
#define UP_2_LOW 'a'-'A'

#define CASE_SENSITIVE 1
#define CASE_INSENSITIVE 0

#define print(x) write(STDOUT_FILENO, x, stringLength(x));
#define printLine(x) write(STDOUT_FILENO, x, stringLength(x)); write(STDOUT_FILENO, "\n", stringLength("\n"));
#define printError(x) write(STDOUT_FILENO, RED, stringLength(RED)); write(STDOUT_FILENO, x, stringLength(x)); write(STDOUT_FILENO, RESET, stringLength(RESET));
#define printColor(x, y) write(STDOUT_FILENO, y, stringLength(y)); write(STDOUT_FILENO, x, stringLength(x)); write(STDOUT_FILENO, RESET, stringLength(RESET));
#define printColorLine(x, y) write(STDOUT_FILENO, y, stringLength(y)); write(STDOUT_FILENO, x, stringLength(x)); write(STDOUT_FILENO, RESET, stringLength(RESET)); write(STDOUT_FILENO, "\n", stringLength("\n"));

/*
 * IDEES D'IMPLEMENTACIÓ:
 * - Per a les funcions estaria interessant tenir diversos arrays on l'index de cadaun sigui una comanda,
 * després a l'hora d'implementar missatges d'error d'us o comprovar quin és la comanda introduida es pot 
 * fer per indexos d'aquests arrays. 
 */

int stringLength(char * string);



char * toLowerCase(char * string){

	char * lowerCase = malloc(sizeof(char) * stringLength(string));

	for (int i = 0; i < stringLength(string); i++){
		if (string[i] >= 'A' && string[i] <= 'Z'){
			lowerCase[i] = string[i] + UP_2_LOW;		
		} else {
			lowerCase[i] = string[i];
		}
	}

	return lowerCase;
}

char * toUpperCase(char * string);  //TODO: priority 2

char * stringCopy(char * origin){

    int i = 0;
    char * destination = NULL;

    while(origin[i] != '\0') {

        destination = realloc(destination, sizeof(char) * (i + 2));
        destination[i] = origin[i];
        i++;
    }

    destination[i] = '\0';
    
    return destination;
}

int stringLength(char * string){

    int count = 0;
    int i = 0;

    while(string[i] != '\0'){
        count++;
        i++;
    }

    return count;
}

int stringCompare(char * string1, char * string2, int caseSensitivity){

    for (int i = 0; i < stringLength(string1); i++){
        
        if (caseSensitivity == CASE_SENSITIVE) {
            if (string1[i] != string2[i]) return EXIT_FAILURE;
        
        } else if (caseSensitivity == CASE_INSENSITIVE) {

            if ((string1[i] != string2[i]) && ((string1[i]+UP_2_LOW) != string2[i]) && ((string1[i]+LOW_2_UP) != string2[i])) return EXIT_FAILURE;
        } else {
            printError("ERROR: Invalid case option :(\n");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}


char * readUntil(int fd, char delimitator){
    char * buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    int i = 0;
    int bytes_read;
    char aux;

    bytes_read = read(fd, &aux, sizeof(char));

    while(aux != delimitator && aux != '\n'){

        if (bytes_read == 0) {
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

void parseArguments(char ** argv, int argc) {

    if (!stringCompare(argv[0], "EXIT", CASE_INSENSITIVE)) {
        printLine(EXIT_MSG);
		exit(EXIT_SUCCESS);
    } else if (!stringCompare(argv[0], "VERSION", CASE_INSENSITIVE)) {
        switch(argc){
            case 1:
                printColorLine(FB_VERSION, GREEN);
                break;
            case 2:
                printError("To be implemented...\n")
                break;
            default:
                printColor(toLowerCase(argv[0]), YELLOW); //toLowerCase (when implemented)
                for (int i = 1; i < argc; i++) {
                    print(" ");
                    printColor(argv[i], YELLOW); //no toLowerCase
                }
                printError(": invalid options\n");
                printColor(toLowerCase(argv[0]), YELLOW); //toLowerCase (when implemented)
                printError(": usage: \n") //to be implemented :)
        }

    } else {
        printColor(toLowerCase(argv[0]), YELLOW);    //toLowerCase (when implemented)
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

    for (int i = 0; i < stringLength(string) + 1; i++) {

        if (string[i] == separator || string[i] == ending) {
            
            if (b_size == 0 && string[i] == separator) continue;
            if (b_size == 0 && string[i] == ending) break;            

            (*argc)++;
            buffer[b_size] = '\0';
            
            argv = realloc(argv, sizeof(char*) * (*argc));
            argv[(*argc) - 1] = malloc(sizeof(char) * b_size);
            
            argv[(*argc) - 1] = stringCopy(buffer);
            
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
        input = readUntil(STDIN_FILENO, '\n');
        argv = getArguments(input, ' ', '\0', &argc);
        if (argc > 0) parseArguments(argv, argc);


        freeArgs(argv, argc);
        free(input);        //implement a buffer of past comands??? ^[[A^[[B^[[C^[[D (READ ^[[...)
    }

    return EXIT_SUCCESS;
}