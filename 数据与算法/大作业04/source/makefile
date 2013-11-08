compile_options=-Os -O3 -std=c++11 -Wall
link_options=-static

.PHONY: all
all: 1 2

1: main1.o binary_search_tree.o
	g++ $(link_options) main1.o binary_search_tree.o -o ../exe/2012011064_1.exe
2: main2.o binary_search_tree.o
	g++ $(link_options) main2.o binary_search_tree.o -o ../exe/2012011064_2.exe

main1.o: binary_search_tree.h main1.cpp
	g++ $(compile_options) main1.cpp -c -o main1.o
main2.o: binary_search_tree.h main2.cpp
	g++ $(compile_options) main2.cpp -c -o main2.o
binary_search_tree.o: binary_search_tree.h binary_search_tree.cpp
	g++ $(compile_options) binary_search_tree.cpp -c -o binary_search_tree.o

.PHONY: clean
clean:
	del main1.o main2.o binary_search_tree.o 2012011064_1.exe 2012011064_2.exe