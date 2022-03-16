OBJS	= instruction.o operand.o
SOURCE	= instruction.c operand.c
HEADER	= instruction.h operand.h
OUT	= instruction
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

instruction.o: instruction.c
	$(CC) $(FLAGS) instruction.c 

operand.o: operand.c
	$(CC) $(FLAGS) operand.c 


clean:
	rm -f $(OBJS) $(OUT)
