OBJ = parser.o main.o
main:$(OBJ)
	g++ -g -o cal $(OBJ)
parser.o: parser.cpp parser.h
	g++ -g -c parser.cpp
main.o: main.cpp parser.h
	g++ -g -c main.cpp

clean:
	-rm -f cal $(OBJ)
