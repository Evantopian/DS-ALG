OBJECTS = List.o Node.o OList.o 
CXXFLAGS = -std=c++11

main: main.o $(OBJECTS) 
	g++ $(CXXFLAGS) -o main main.o $(OBJECTS) 

main.o: main.cpp List.h Node.h
	g++ -c main.cpp


tests: tests.o $(OBJECTS)
	g++ $(CXXFLAGS) -o tests tests.o $(OBJECTS)

test.o: tests.cpp OList.h


List.o: List.cpp List.h Node.h
	g++ -c List.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

OList.o: OList.cpp OList.h Node.h
	g++ -c OList.cpp



clean:
	rm -rf *.o main tests
