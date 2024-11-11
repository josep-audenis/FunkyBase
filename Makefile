all: main


main: main.o string.o io.o
	gcc ./build/main.o ./build/string.o ./build/io.o -o ./bin/main.exe -Wall -Wextra
 
main.o: ./src/main.c
	gcc -c ./src/main.c -o ./build/main.o -Wall -Wextra



string.o: ./src/string.c ./include/string.h ./include/io.h
	gcc -c ./src/string.c -o ./build/string.o -Wall -Wextra

io.o: ./src/io.c ./include/io.h
	gcc -c ./src/io.c -o ./build/io.o -Wall -Wextra


clean:
	rm -f ./build/*.o ./bin/*.exe