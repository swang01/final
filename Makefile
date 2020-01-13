all: client.o
	gcc -o client.out client.o -lncurses

client.o: client.c
	gcc -c client.c

sub_server.o: sub_server.c
	gcc -c sub_server.c

clean:
	rm *.o
	rm *.out
	rm *~

run:
	./client.out
