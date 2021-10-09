syscall: main.o myop.o
	gcc -o syscall main.o myop.o

main.o : main.c myheader.h
	gcc -c main.c myheader.h

myop.o : myop.c myheader.h
	gcc -c myop.c myheader.h
