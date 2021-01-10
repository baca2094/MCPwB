# compilador
CC = g++

# flags

main: main.o camion.o mcpwb.o 
	g++ main.o camion.o mcpwb.o -o MCPwB
	
main.o: main.cpp 
	g++ -c main.cpp

camion.o: camion.h

mcpwb.o: mcpwb.h

clean:
	rm *.o MCPwB
