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
  pargarph: a pointer to the current position in the paragraph being typed
  c: a char to check against
  if: c matches char at the beginning of the paragraph, paragraph gets incremented by 1 (character was typed correctly)
  else: nothing happens
  returns the "updated" pointer (position in paragraph)
*/
char * char_check(char * paragraph, char * c){
  if (!strcmp(c, paragraph)){
    paragraph++;
  }
  return paragraph;
}
int main(){
  int fd;
  FILE *f;
  char buffer[1024];
  char c[1];
  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  // fd = open("paragraph.txt", O_RDONLY);
  // if (fd < 0){
  //   printf("Error: %s\n", strerror(errno));
  //   return 1;
  // }
  fgets(buffer, 1024, f);
  buffer[strlen(buffer) - 1] = '\0';
  // printf("\033[2J");
  printf("paragraph: %s\n", buffer);
  printf("Enter some letter: \n");
  fgets(c, 1, stdin);
  c[strlen(c) - 1] = '\0';
  printf("You typed: %s\n", c);
  while(1){
    fgets(c, 1, stdin);
    c[strlen(c) - 1] = '\0';
    // if (c){
    //   printf("You typed: %s\n", c);
    //
    // }
  }
  // while(buffer){
  //   printf("%s\n", buffer);
  //   scanf("%s", a_word);
  //   fgets(c, 1, stdin);
  //   printf("\033[2J");
  //   strcpy(buffer, char_check(buffer, c));
  // }
  printf("Race over!\n");
  // close(fd);
}
