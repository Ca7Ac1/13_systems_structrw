all: main.o csv.o interact.o
	gcc -o main main.o csv.o interact.o

main.o: main.c interact.h csv.h
	gcc -c main.csv

csv.o: csv.c csv.h
	gcc -c csv.c

interact.o: interact.c interact.h
	gcc -c interact.c
