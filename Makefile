calc: Calculator.o BigInt.o main.o
	g++ -o calc main.o Calculator.o BigInt.o

main.o: main.cpp Calculator.h
	g++ -c main.cpp

Calculator.o: Calculator.h Calculator.cpp
	g++ -c Calculator.cpp Calculator.h

BigInt.o: BigInt.h BigInt.cpp
	g++ -c BigInt.h BigInt.cpp

clean:
	rm -f *.o *.gch calc
