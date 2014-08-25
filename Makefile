OBJS = cpu.o mem.o picovm.o main.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c -std=c99 $(DEBUG)
LDFLAGS = -Wall -g

picovm: $(OBJS)
	$(CC) $(LFLAGS) -o picovm $(OBJS)

mem.o: mem.h picovm.h mem.c
	$(CC) $(CFLAGS) -o mem.o mem.c

cpu.o: cpu.h mem.h picovm.h cpu.c
	$(CC) $(CFLAGS) -o cpu.o cpu.c

picovm.o: picovm.h picovm.c
	$(CC) $(CFLAGS) -o picovm.o picovm.c

main.o: cpu.h mem.h picovm.h main.c
	$(CC) $(CFLAGS) -o main.o main.c
