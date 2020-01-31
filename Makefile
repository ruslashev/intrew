cflags = -Wall -g -Wno-unused-function

all:
	gcc main.c -o main $(cflags)
	./main

