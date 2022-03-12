OBJS	= preassembler.o macro_list.o
SOURCE	= preassembler.c macro_list.c
HEADER	= macro_list.h
OUT	= preassembler
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

preassembler.o: preassembler.c
	$(CC) $(FLAGS) preassembler.c 

macro_list.o: macro_list.c
	$(CC) $(FLAGS) macro_list.c 


clean:
	rm -f $(OBJS) $(OUT)