OBJS	= util.o symbol_list.o
SOURCE	= util.c symbol_list.c
HEADER	= util.h symbol_list.h
OUT	= symbol_list
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

util.o: util.c
	$(CC) $(FLAGS) util.c 

symbol_list.o: symbol_list.c
	$(CC) $(FLAGS) symbol_list.c 


clean:
	rm -f $(OBJS) $(OUT)
