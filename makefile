OBJS	= main.o parser.o data_list.o instruction_list_pass1.o  operand.o symbol_list.o util.o opcode.o instruction_pass2.o writer.o macro_list.o preassembler.o
SOURCE	= main.c parser.c data_list.c instruction_list_pass1.c  operand.c symbol_list.c util.c opcode.c instruction_pass2.c writer.c macro_list.c preassembler.c
HEADER	=        parser.h data_list.h instruction_list_pass1.h  operand.h symbol_list.h util.h opcode.h instruction_pass2.h writer.h macro_list.h preassembler.h
OUT	= assembler
CC	 = gcc
FLAGS	 = -g -c -Wall -ansi -pedantic
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

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

instruction_pass2.o: instruction_pass2.c
	$(CC) $(FLAGS) instruction_pass2.c 

writer.o: writer.c
	$(CC) $(FLAGS) writer.c 

macro_list.o: macro_list.c
	$(CC) $(FLAGS) macro_list.c 

preassembler.o: preassembler.c
	$(CC) $(FLAGS) preassembler.c 

clean:
	rm -f $(OBJS) $(OUT)
