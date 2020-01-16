all: client.o sub_server.c main_server.c
	gcc -o client.out client.o sub_server.o  main_server.o -lncurses

client.o: client.c
	gcc -c client.c

sub_server.o: sub_server.c
	gcc -c sub_server.c

main_server.o: main_server.c
	gcc -c main_server.c

clean:
	rm *.o
	rm *.out
	rm *~

run:
	./client.out
