#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>
#include <stdlib.h>

#define LOW_2_UP 'A'-'a'
#define UP_2_LOW 'a'-'A'

#define CASE_SENSITIVE 1
#define CASE_INSENSITIVE 0

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int STRING_length(char * string);
char * STRING_toLowerCase(char * string);
char * STRING_toUpperCase(char * string);
char * STRING_copy(char * origin);
int STRING_compare(char * string1, char * string2, int caseSensitivity);



#endif