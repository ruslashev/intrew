cflags = -Wall -g -Wno-unused-function -fsanitize=address

all:
	gcc main.c -o main $(cflags)
	./main

