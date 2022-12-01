OBJECTS = BSTree.o Node.o
CXXFLAGS = -std=c++11

main: main.o $(OBJECTS) 
	g++ $(CXXFLAGS) -o main main.o $(OBJECTS) 

main.o: main.cpp BSTree.h Node.h
	g++ -c main.cpp

tests: tests.o $(OBJECTS)
	g++ $(CXXFLAGS) -o tests tests.o $(OBJECTS)

test.o: tests.cpp doctest.h 
	g++ -c tests.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

BSTree.o: BSTree.cpp BSTree.h Node.h
	g++ -c BSTree.cpp

clean:
	rm -rf *.o main tests
