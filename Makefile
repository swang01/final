all: client.o sub_server.o
	gcc -o client.out client.o sub_server.o -lncurses

forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o -lncurses

fserver: forking_server.o networking.o
	gcc -o server forking_server.o networking.o

sclient: select_client.o networking.o
	gcc -o client select_client.o networking.o -lncurses

client.o: client.c
	gcc -c client.c

# sub_server.o: sub_server.c
# 	gcc -c sub_server.c

forking_server.o: forking_server.c networking.h
	gcc -c forking_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *.out
	rm *~

run:
	./client.out
