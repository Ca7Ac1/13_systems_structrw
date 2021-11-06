all: main.o csv.o interact.o
	gcc -o main main.o csv.o interact.o


