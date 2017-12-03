warnings = -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable \
		   -Wduplicated-cond -Wduplicated-branches -Wdouble-promotion \
		   -Wnull-dereference -Wformat=2 -Wdisabled-optimization \
		   -Wsuggest-override -Wlogical-op -Wtrampolines -Wfloat-equal
flags = -ggdb3 -Og -std=c++0x -fno-rtti -fno-exceptions

o:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	echo "4 1 1 2 1" | ./main

all:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	@./main

