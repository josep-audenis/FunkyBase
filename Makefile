all: main


main: main.o
	gcc ./build/main.o -o ./bin/main.exe -Wall -Wextra
 
main.o: ./src/main.c
	gcc -c ./src/main.c -o ./build/main.o -Wall -Wextra


clean:
	rm -f ./build/*.o ./bin/*.exe