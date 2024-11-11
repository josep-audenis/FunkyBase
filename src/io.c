#include "../include/io.h"

char * IO_readUntil(int fd, char delimitator){
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