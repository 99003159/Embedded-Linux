SRC= *.c  INC= *.h

all: sum.o square.o main.o
	arm-linux-gnueabi-gcc *.o *.h -o a.out

run:
	./a.out

sum.o: sum.c
	arm-linux-gnueabi-gcc -c sum.c -o sum.o

square.o:square.c
	arm-linux-gnueabi-gcc -c square.c -o square.o

main.o:main.c
	arm-linux-gnueabi-gcc -c main.c -o main.o
clean:
	rm -rf *.o *.out
