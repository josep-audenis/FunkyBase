#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define RED "\x1B[31m" 
#define GREEN "\x1B[32m" 
#define YELLOW "\x1B[33m" 
#define BLUE "\x1B[34m" 
#define MAGENTA "\x1B[35m" 
#define CYAN "\x1B[36m" 
#define RESET "\x1B[0m"

#define print(x) write(STDOUT_FILENO, x, STRING_length(x));
#define printLine(x) write(STDOUT_FILENO, x, STRING_length(x)); write(STDOUT_FILENO, "\n", STRING_length("\n"));
#define printError(x) write(STDOUT_FILENO, RED, STRING_length(RED)); write(STDOUT_FILENO, x, STRING_length(x)); write(STDOUT_FILENO, RESET, STRING_length(RESET));
#define printColor(x, y) write(STDOUT_FILENO, y, STRING_length(y)); write(STDOUT_FILENO, x, STRING_length(x)); write(STDOUT_FILENO, RESET, STRING_length(RESET));
#define printColorLine(x, y) write(STDOUT_FILENO, y, STRING_length(y)); write(STDOUT_FILENO, x, STRING_length(x)); write(STDOUT_FILENO, RESET, STRING_length(RESET)); write(STDOUT_FILENO, "\n", STRING_length("\n"));

char * IO_readUntil(int fd, char delimitator);

#endif