Main: Main.o Graph.o
	g++ -g Main.o Graph.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

Graph.o: ./Graph.cpp
	g++ -c ./Graph.cpp
	
clean: 
	rm *.o Main 