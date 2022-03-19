OBJS	= parser.o data_list.o instruction_list_pass1.o  operand.o symbol_list.o util.o opcode.o
SOURCE	= parser.c data_list.c instruction_list_pass1.c  operand.c symbol_list.c util.c opcode.c
HEADER	= data_list.h instruction_list_pass1.h  operand.h symbol_list.h util.h opcode.h
OUT	= parser
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

parser.o: parser.c
	$(CC) $(FLAGS) parser.c 

data_list.o: data_list.c
	$(CC) $(FLAGS) data_list.c 

instruction_list_pass1.o: instruction_list_pass1.c
	$(CC) $(FLAGS) instruction_list_pass1.c 

operand.o: operand.c
	$(CC) $(FLAGS) operand.c 

symbol_list.o: symbol_list.c
	$(CC) $(FLAGS) symbol_list.c 

util.o: util.c
	$(CC) $(FLAGS) util.c 

opcode.o: opcode.c
	$(CC) $(FLAGS) opcode.c 


clean:
	rm -f $(OBJS) $(OUT)
