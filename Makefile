all: client.o
	gcc -o client.out client.o

client.o: client.c
	gcc -c client.c

clean:
	rm *.o
	rm *.out
	rm *~

run:
	./client.out
