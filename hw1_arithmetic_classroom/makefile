OBJS=hw1_PAC.o hw1_calculator.o
main: $(OBJS)
	g++ -g -o hw1 $(OBJS)
PAC.o:hw1_PAC.cpp hw1_calculator.h
	g++ -g -c hw1_PAC.cpp
Calculator.o:hw1_calculator.cpp hw1_calculator.h
	g++ -g -c hw1_calculator.cpp
clean:
	-rm -f hw1 $(OBJS) 
