main: Person.o Node.o List.o Dictionary.o main.o
	g++ -o main Person.o Node.o List.o Dictionary.o main.o

tests: Person.o Node.o List.o Dictionary.o tests.o
	g++ -o tests Person.o Node.o List.o Dictionary.o tests.o


main.o: Dictionary.h main.cpp

tests.o: tests.cpp Dictionary.h

Person.o: Person.h Person.cpp

Node.o: Node.h Node.cpp Person.h

List.o: List.h List.cpp Node.h

Dictionary.o: Dictionary.h Dictionary.cpp List.h


clean:
	rm -f *.o main tests
