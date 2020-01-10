#include "headers.h"
#include "networking.h"

// #include <sys/wait.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <conio.h> //to get unbuffered input (and also doesn't work T-T)

/* char_check(char * paragraph, char c)
  paragraph: a pointer to the current position in the paragraph being typed
  typed: a pointer for the letters typed already
  c: a char to check against
  if: c matches char at the beginning of the paragraph, paragraph gets incremented by 1 (character was typed correctly)
  else: nothing happens
  returns paragraph shifted over one char if c matched the first char of paragraph
          otherwise returns the unchanged paragraph
*/
char * char_check(char * paragraph, char * typed, char c){
  // printf("paragraph: %s \n c: %s\n", paragraph, c);
  // printf("paragraph[0]: %c | c[0]: %c\n", paragraph[0], c[0]);
  if (c == paragraph[0]){ //correctly typed
    paragraph++; //update the part to still type
    strcat(typed, &c); //update the typed part
    // printf("updated paragraph: %s\n", paragraph);
  }
  return paragraph;
}


int main(int argc, char **argv){
  int fd;
  FILE *f;
  char paragraph[PAR_LEN];
  char typed[PAR_LEN * 2] = "";
  // char c[10];
  char c;
  // ---------------------------------------------------------------------------
  // getting paragraph content from text file
  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  fgets(paragraph, PAR_LEN, f);
  paragraph[strlen(paragraph) - 1] = '\0';
  printf("\033[2J");
  printf("'%s'\n", paragraph);
  fflush(stdout);
  // flush buffer to immediately print
  //----------------------------------------------------------------------------

  //getting user input (still need to utilize curses instead of basic stdin)
  while(paragraph && strcmp(paragraph, "")){
    c = getchar();
    getchar(); //"absorbs" '\n' from pressing ENTER
    if (c != '\r' && c != EOF && c != '\t'){
      strcpy(paragraph, char_check(paragraph, typed, c));
      printf("\033[2J");
      printf("TYPE!!!!\n\n\n\n");
      printf("Typed: '%s'\n\n", typed);
      printf("> '%s' \n", paragraph);
      // printf("Typed: '%s' | length of typed: %d\n\n\n", typed, strlen(typed));
      // printf("'%s' | length of paragraph: %d\n", paragraph, strlen(paragraph));
      //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(server_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
    }//end stdin select

    //currently the server is not set up to
    //send messages to all the clients, but
    //this would allow for broadcast messages
    if (FD_ISSET(server_socket, &read_fds)) {
      read(server_socket, buffer, sizeof(buffer));
      printf("[SERVER BROADCAST] [%s]\n", buffer);
      printf("enter data: ");
      //the above printf does not have \n
      //flush the buffer to immediately print
      fflush(stdout);
    }//end socket select
  }
  printf("Race over!\n");
  fclose(f);
}
