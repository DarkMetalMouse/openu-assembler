OBJS	= parser.o util.o symbol_list.o
SOURCE	= parser.c util.c symbol_list.c
HEADER	= util.h symbol_list.h
OUT	= parser
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

parser.o: parser.c
	$(CC) $(FLAGS) parser.c 

util.o: util.c
	$(CC) $(FLAGS) util.c 

symbol_list.o: symbol_list.c
	$(CC) $(FLAGS) symbol_list.c 


clean:
	rm -f $(OBJS) $(OUT)
