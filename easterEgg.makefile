CFLAGS=-Wall -std=c89 -g
LIBS=-lcheck

all: easterEgg

easterEgg: easterEgg.o functions.o
	gcc -o easterEgg easterEgg.o functions.o

easterEgg.o: easterEgg.c functions.h
	gcc $(CFLAGS) -c easterEgg.c

functions.o: functions.c functions.h
	gcc $(CFLAGS) -c functions.c

test: easterEgg-test
	./easterEgg-test

easterEgg-test: functions-test.o functions.o
	gcc -o easterEgg-test functions.o functions-test.o $(LIBS)

functions-test.o: functions-test.c functions.h
	gcc $(CFLAGS) -c functions-test.c

functions-test.c: functions-test.check
	checkmk functions-test.check > functions-test.c
