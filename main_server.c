#include "headers.h"

#include "networking.h"

void process(char *s);
void subserver(int from_client, int writefd);

int main() {

  int listen_socket;
  int client_socket;
  int f;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];
  char statsbuffer[BUFFER_SIZE]; //storing stats

  //unnamed pipes for transferring info b/c server and subserver
  int ss1[2];
  int ss2[2];
  int ss3[2];
  int ss4[2];

  int * pipes[4] = {ss1, ss2, ss3, ss4};
  pipe(ss1);
  pipe(ss2);
  pipe(ss3);
  pipe(ss4);

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
     //returns socket descriptor for new socket connected

     f = fork();
     if (f == 0) //child
      close(pipes[subserver_count][0]); //close the read end of the corresponding pipe
       subserver(client_socket, pipes[subserver_count][1]);
       //also have to pass the pipe write fd
     }
     else {
       subserver_count++;
       close(pipes[subserver_count - 1][1]);
       //close the write end of the corresponding pipe

       read(statsfd, statsbuffer, sizeof(statsbuffer));
       printf("Server received: %s\n", statsbuffer);
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

void subserver(int client_socket, int writefd) {
  char buffer[BUFFER_SIZE];

  //for testing client select statement
  strncpy(buffer, "hello client", sizeof(buffer));
  write(writefd, buffer, sizeof(buffer));

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(writefd, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) { //to be replaced with stat calculations
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
