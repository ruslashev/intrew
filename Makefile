warnings = -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable \
           -Wduplicated-cond -Wduplicated-branches -Wdouble-promotion \
           -Wnull-dereference -Wformat=2 -Wdisabled-optimization \
           -Wsuggest-override -Wlogical-op -Wtrampolines -Wfloat-equal
flags = -ggdb3 -O2 -std=c++14 -fno-rtti -fno-exceptions

all:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	./main

o:
	@echo Compiling main.cc to main
	@g++ main.cc $(flags) $(warnings) -o main
	cat test_case | ./main

