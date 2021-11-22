Replace: main.o fifo.o opt.o lru.o second_chance.o
	gcc -o Replace main.o fifo.o opt.o lru.o second_chance.o

main.o : main.c header.h
	gcc -c main.c header.h

fifo.o : fifo.c header.h
	gcc -c fifo.c header.h

opt.o : opt.c header.h
	gcc -c opt.c header.h
lru.o : lru.c header.h
	gcc -c lru.c header.h

second_chance.o : second_chance.c header.h
	gcc -c second_chance.c header.h
