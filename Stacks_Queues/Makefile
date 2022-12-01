OBJECTS = stack.o queue.o Node.o OList.o  
CXXFLAGS = -std=c++11

main: main.o $(OBJECTS) 
	g++ -o main main.o $(OBJECTS)

tests: tests.o $(OBJECTS) 
	g++ -o tests tests.o $(OBJECTS) 

tests.o: tests.cpp doctest.h
	g++ -c tests.cpp

main.o: main.cpp stack.h
	g++ -c main.cpp

stack.o: stack.cpp stack.h
	g++ -c stack.cpp

queue.o: queue.cpp queue.h
	g++ -c queue.cpp

OList.o: OList.cpp OList.h
	g++ -c OList.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

clean:
	rm -f *.o
