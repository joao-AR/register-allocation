Main: Main.o Graph.o Stack.o
	g++ -g Main.o Graph.o Stack.o -o regalloc

Main.o: Main.cpp
	g++ -c Main.cpp

Graph.o: ./Graph.cpp
	g++ -c ./Graph.cpp

Stack.o: ./Stack.cpp
	g++ -c ./Stack.cpp

clean: 
	rm *.o regalloc 