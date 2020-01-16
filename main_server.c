#include "headers.h"

#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int client_socket;
  int f;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];
  char statsbuffer[BUFFER_SIZE]; //storing stats

  //unnamed pipes for transferring info b/c server and subserver
  int ss0[2];
  int ss1[2];
  int ss2[2];
  int ss3[2];

  int pipes[4][2] = {ss0, ss1, ss2, ss3}; 
  pipe(ss0);
  pipe(ss1);
  pipe(ss2);
  pipe(ss3);

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
       subserver(client_socket);
     else {
       subserver_count++;
       int statsfd = open("stats", O_RDONLY);
       read(statsfd, statsbuffer, sizeof(statsbuffer));
       printf("Server received: %s\n", statsbuffer);
       close(client_socket);
       close(statsfd);
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

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  //for testing client select statement
  strncpy(buffer, "hello client", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
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
  char buffer[BUFFER_SIZE];
  strncpy(buffer, "sample stats here: wpm ?? | accuracy ??", sizeof(buffer));
  int statsfd = open("stats", O_WRONLY); //write the data into the FIFO
  write(statsfd, buffer, sizeof(buffer));
  close(statsfd);
}
