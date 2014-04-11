compile_options=-O3 -Os -std=c++11 -Wall
link_options=-static

ARCH="`uname -s`"
LINUX=Linux

2012011064: 2012011064.o 
	g++ $(link_options) ../obj/2012011064.o -o ../exe/2012011064
2012011064.o: 2012011064.cpp
	g++ $(compile_options) 2012011064.cpp -c -o ../obj/2012011064.o

test: 2012011064
	"../exe/2012011064" < "../exe/input.txt" > "../exe/output.txt" 

generate: generate.o
	g++ $(link_options) ../obj/generate.o -o ../exe/generate
generate.o: generate.cpp
	g++ $(compile_options) generate.cpp -c -o ../obj/generate.o

.PHONY: clean
clean:
	@if [ $(ARCH) = $(LINUX) ]; \
	then \
		rm -f "../exe/2012011064" "../obj/*.o"; \
	else \
		del /Q "../exe/*.exe" "../obj/*.o"; \
	fi
