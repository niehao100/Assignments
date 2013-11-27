compile_options=-O3 -Os -std=c++11 -Wall
link_options=-static

2012011064: main.o record.o 
	g++ $(link_options) ../obj/main.o ../obj/record.o -o ../exe/2012011064
main.o: record.h main.cpp
	g++ $(compile_options) main.cpp -c -o ../obj/main.o
record.o: record.h record.cpp
	g++ $(compile_options) record.cpp -c -o ../obj/record.o

#这玩意是用来产生测试数据的
#generate: generate.o
#	g++ ../obj/generate.o -o ../exe/generate.exe
#generate.o: generate.cpp
#	g++ $(compile_options) generate.cpp -c -o ../obj/generate.o

#这玩意用来跑默认的命令参数
.PHONY: test
test: 2012011064
	../exe/2012011064.exe ../exe/input_ori.txt ../exe/output_num.txt \
../exe/output_sco.txt ../exe/output_search.txt ../exe/input_new.txt \
../exe/output_update.txt ../exe/input_del.txt ../exe/output_del.txt

.PHONY: clean
clean:
	del /Q "../exe/*.exe" "../obj/*.o"