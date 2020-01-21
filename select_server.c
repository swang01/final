#include "headers.h"
#include "networking.h"

void process(char *s);
void subserver(int from_client, int num_players);
int isnumber(char * str);

int main() {

  int listen_socket;
  int client_socket;
  int f;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];

  int num_players = 0;
  struct player_data* players[MAX_PLAYERS];
  
  //set of file descriptors to read from
  fd_set read_fds;

  listen_socket = server_setup();

  while (1) {

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds); //0 out fd set
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(listen_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    //if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {
     client_socket = server_connect(listen_socket);

     f = fork();
     if (f == 0){
       subserver(client_socket, num_players);
       num_players ++;
     }
     else {
       subserver_count++;
       close(client_socket);
     }
    }//end listen_socket select

    //if stdin triggered select
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      //if you don't read from stdin, it will continue to trigger select()
      fgets(buffer, sizeof(buffer), stdin);
      printf("[server] subserver count: %d\n", subserver_count);
    }//end stdin select
  }
}

void subserver(int client_socket, int num_players) {
  char buffer[BUFFER_SIZE];

  //for testing client select statement
  while (read(client_socket, buffer, sizeof(buffer))) {
    if (!(isnumber(buffer))){
      if (num_players > 4){
	strncpy(buffer, FULL, sizeof(buffer));
	write(client_socket, buffer, sizeof(buffer));
      }
      else{
	struct player_data* new_player;
	strcpy(new_player->username , buffer);
      }
    }
    //else {
      printf("[subserver %d] received: [%s]\n", getpid(), buffer);
      //process(buffer);
      write(client_socket, buffer, sizeof(buffer));
      // }
  }//end read loop
  close(client_socket);
  exit(0);
}

int isnumber(char * str){
  while(*str){
    if (isdigit(*str++) == 0) return 0;
  }
  return 1;
}
