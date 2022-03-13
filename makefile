OBJS	= instruction_list.o
SOURCE	= instruction_list.c
HEADER	= 
OUT	= instruction_list
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

instruction_list.o: instruction_list.c
	$(CC) $(FLAGS) instruction_list.c 


clean:
	rm -f $(OBJS) $(OUT)
