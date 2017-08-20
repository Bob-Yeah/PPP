OBJ = parser.o main.o
main:$(OBJ)
	g++ -Wall -g -o cal $(OBJ)
parser.o: parser.cpp parser.h
	g++ -Wall -g -c parser.cpp
main.o: main.cpp parser.h
	g++ -Wall -g -c main.cpp

clean:
	-rm -f cal $(OBJ)
