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
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

/*
  char_check(char * paragraph, char c)
  pargarph: a pointer to the current position in the paragraph being typed
  c: a char to check against
  if: c matches char at the beginning of the paragraph, paragraph gets incremented by 1 (character was typed correctly)
  else: nothing happens
  returns the "updated" pointer (position in paragraph)
*/
char * char_check(char * paragraph, char c){
  if (!strcmp(c, paragraph)){
    paragraph++;
  }
  return paragraph;
}
int main(){
  int fd;
  char[1024] buffer;
  char[1] c;
  fd = open("paragraph.txt", O_RDONLY);
  fgets(buffer, 1024, fd);
  printf("paragraph: %s\n", buffer);
  while(buffer){
    printf("\033[2J");
    printf("%s\n", buffer);
    fgets(c, 1, stdin);
    char_check(buffer, c);
  }
}
