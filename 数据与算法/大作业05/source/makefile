compile_options=-O3 -Os -std=c++11
link_options=-static


2012011064: main.o
	g++ $(link_options) main.o -o ../exe/2012011064.exe
main.o: main.cpp
	g++ $(compile_options) main.cpp -c -o main.o

#这玩意是用来产生测试数据的
generate: generate.o
	g++ $(global_options) generate.o -o generate.exe
generate.o: generate.cpp
	g++ $(compile_options) generate.cpp -c -o generate.o

.PHONY: clean
clean:
	del /Q 2012011064.exe main.o generate.exe generate.o input_v*_e*_*.txt