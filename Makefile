all: client.o
	gcc -o client client.o

client.o: client.c
	gcc -c client.c

clean:
	rm *.o
	rm *~

run:
	./client.out
