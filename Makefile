select: sclient sserver

sserver: main_server.o networking.o
	gcc -o server main_server.o networking.o

sclient: client.o networking.o
	gcc -o client client.o networking.o -lncurses

client.o: client.c networking.h
	gcc -c client.c -lncurses

main_server.o: main_server.c networking.h
	gcc -c main_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *.out
	rm *~
