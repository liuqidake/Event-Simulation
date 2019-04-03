
CC = clang++

CFLAGS = -c -Wall

all: simulator

simulator: main.o EventSimulator.o BankSimulator.o SupermarketSimulator.o
	$(CC) -o simulator main.o EventSimulator.o BankSimulator.o SupermarketSimulator.o
main.o:main.cpp
	$(CC) $(CFLAGS) main.cpp
EventSimulator.o:EventSimulator.cpp
	$(CC) $(CFLAGS) EventSimulator.cpp
BankSimulator.o:BankSimulator.cpp
	$(CC) $(CFLAGS) BankSimulator.cpp
SupermarketSimulator.o:SupermarketSimulator.cpp
	$(CC) $(CFLAGS) SupermarketSimulator.cpp

clean:
	rm -rf *.o simulator 
