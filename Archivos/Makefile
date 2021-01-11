# compilador
CC = g++

# flags

CFLAGS = -g 
main: main.o camion.o mcpwb.o 
	$(CC) $(CFLAGS) main.o camion.o mcpwb.o -o MCPwB
	
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

camion.o: camion.h

mcpwb.o: mcpwb.h

clean:
	rm *.o MCPwB
