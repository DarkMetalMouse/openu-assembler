OBJS	= data_list.o
SOURCE	= data_list.c
HEADER	= data_list.h
OUT	= data_list
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

data_list.o: data_list.c
	$(CC) $(FLAGS) data_list.c 


clean:
	rm -f $(OBJS) $(OUT)
