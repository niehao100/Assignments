compile_options=-static -O3 -Os -std=c++11 -Wall

2012011064: main.o
	g++ ../obj/main.o -o ../exe/2012011064.exe
main.o: main.cpp
	g++ $(compile_options) main.cpp -c -o ../obj/main.o

#这玩意是用来产生测试数据的
generate: generate.o
	g++ ../obj/generate.o -o ../exe/generate.exe
generate.o: generate.cpp
	g++ $(compile_options) generate.cpp -c -o ../obj/generate.o

.PHONY: clean
clean:
	del /Q "../exe/2012011064.exe" "../obj/main.o" "../exe/generate.exe" "../obj/generate.o" "../exe/input_v*_e*_*.txt"