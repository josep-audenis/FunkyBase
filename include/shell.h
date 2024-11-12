#ifndef __SHELL_H__
#define __SHELL_H__



void SHELL_parseArguments(char ** argv, int argc);
char** SHELL_getArguments(char * string, char separator, char ending, int * argc);
void SHELL_freeArgs(char ** argv, int argc);

#endif