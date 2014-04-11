compile_options=-O3 -Os -std=c++11 -Wall -Wl,--heap,800000000
link_options=-static

ARCH="'uname -s'"
LINUX=Linux

2012011064: 2012011064.o 
	g++ $(link_options) ../obj/2012011064.o -o ../exe/2012011064
2012011064.o: 2012011064.cpp
	g++ $(compile_options) 2012011064.cpp -c -o ../obj/2012011064.o
	
check_exe: check.o 
	g++ $(link_options) ../obj/check.o -o ../exe/check
check.o: check.cpp
	g++ $(compile_options) check.cpp -c -o ../obj/check.o

test: 2012011064
	"../exe/2012011064" "../exe/Random.in" "../exe/Random.out"
	"../exe/2012011064" "../exe/Single.in" "../exe/Single.out"
	"../exe/2012011064" "../exe/Increasing.in" "../exe/Increasing.out"
	"../exe/2012011064" "../exe/Decreasing.in" "../exe/Decreasing.out"
	

check: check_exe generate 2012011064
	"../exe/generate"
	mv *.in "../exe/"
	"../exe/2012011064" "../exe/Random.in" "../exe/Random.out"
	"../exe/2012011064" "../exe/Single.in" "../exe/Single.out"
	"../exe/2012011064" "../exe/Increasing.in" "../exe/Increasing.out"
	"../exe/2012011064" "../exe/Decreasing.in" "../exe/Decreasing.out"
	"../exe/check" "../exe/Random.in" "../exe/Random.out"
	"../exe/check" "../exe/Single.in" "../exe/Single.out"
	"../exe/check" "../exe/Increasing.in" "../exe/Increasing.out"
	"../exe/check" "../exe/Decreasing.in" "../exe/Decreasing.out"

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
