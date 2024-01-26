CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -g
OBJ = main.o printMap.o newSleep.o wireSim.o
EXEC = wireworld

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

printMap.o : printMap.c printMap.h 
	$(CC) -c printMap.c $(CFLAGS)

wireSim.o : wireSim.c wireSim.h 
	$(CC) -c wireSim.c $(CFLAGS)

main.o : main.c printMap.h wireSim.h newSleep.h
	$(CC) -c main.c $(CFLAGS)

newSleep.o : newSleep.c newSleep.h
	$(CC) -c newSleep.c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)