#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
// #include <sys/wait.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>

/*
  char_check(char * paragraph, char c)
  paragarph: a pointer to the current position in the paragraph being typed
  c: a char to check against
  if: c matches char at the beginning of the paragraph, paragraph gets incremented by 1 (character was typed correctly)
  else: nothing happens
  returns 0 if nothing changed
  returns 1 if paragraph was changed
*/
int char_check(char * paragraph, char * c){
  printf("paragraph: %s| c: %s\n", paragraph, c);
  printf("paragraph[0]: %c | c[0]: %c\n", paragraph[0], c[0]);
  if (c[0] == paragraph[0]){ //correctly typed
    paragraph++;
    printf("updated paragraph: %s\n", paragraph);
    return 1;
  }
  return 0;
}
int main(){
  int fd;
  FILE *f;
  char paragraph[1024];
  char c[10];
  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  fgets(paragraph, 1024, f);
  paragraph[strlen(paragraph) - 1] = '\0';
  // printf("\033[2J");
  printf("paragraph: %s\n", paragraph);
  while(paragraph){
    fgets(c, 10, stdin);
    c[strlen(c) - 1] = '\0';
    char_check(paragraph, c);
      // printf("\033[2J");
      // printf("Updated: %s\n", paragraph);
    printf("You typed: %s\n", c);
  }
  printf("Race over!\n");
  // fclose(f);
}
