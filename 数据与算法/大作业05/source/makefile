objects=main.o
binary=2012011064

2012011064: $(objects)
	g++ $(objects) -o $(binary) -std=c++11 -static
main.o:
	g++ main.cpp -c -o main.o

.PHONY: clean
clean:
	rm $(binary) $(objects)