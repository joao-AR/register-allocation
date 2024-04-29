Main: Main.o 
	g++ -g Main.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

# Parsing.o: ./Parsing/Parsing.cpp
# 	g++ -c ./Parsing/Parsing.cpp
	
clean: 
	rm *.o Main 