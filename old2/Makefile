warnings = -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
flags = -g -O2

c:
	@echo Compiling main.cc to main
	@g++ main.c $(flags) $(warnings) -o main
	./main

all:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	./main

o:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	cat test_case | ./main

