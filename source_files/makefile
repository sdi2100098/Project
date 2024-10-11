build : main.o Read_Vector.o
	g++ -o build main.o Read_Vector.o

main.o : main.cpp Library.hpp
	g++ -c main.cpp 

Read_Vector.o : Read_Vector.cpp Library.hpp
	g++ -c Read_Vector.cpp
