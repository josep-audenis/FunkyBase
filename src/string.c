#include "../include/string.h"
#include "../include/io.h"
#include "../include/message.h"

int STRING_length(char * string){

    int count = 0;
    int i = 0;

    while(string[i] != '\0'){
        count++;
        i++;
    }

    return count;
}

char * STRING_toLowerCase(char * string){

	char * lowerCase = malloc(sizeof(char) * STRING_length(string));

	for (int i = 0; i < STRING_length(string); i++) {

		if (string[i] >= 'A' && string[i] <= 'Z') {

			lowerCase[i] = string[i] + UP_2_LOW;		
		} else {
			lowerCase[i] = string[i];
		}
	}

	return lowerCase;
}


char * STRING_toUpperCase(char * string){

	char * upperCase = malloc(sizeof(char) * STRING_length(string));

	for (int i = 0; i < STRING_length(string); i++) {

		if (string[i] >= 'a' && string[i] <= 'z') {

			upperCase[i] = string[i] + LOW_2_UP;
		} else {
			upperCase[i] = string[i];
		}
	}

	return upperCase;
}

char * STRING_copy(char * origin){

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

int STRING_compare(char * string1, char * string2, int caseSensitivity){

    for (int i = 0; i < STRING_length(string1); i++){
        
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