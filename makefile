OBJS	= instruction.o
SOURCE	= instruction.c
HEADER	= 
OUT	= instruction
CC	 = gcc
FLAGS	 = -g -c -Wall -ansi -pedantic
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

instruction.o: instruction.c
	$(CC) $(FLAGS) instruction.c 


clean:
	rm -f $(OBJS) $(OUT)
