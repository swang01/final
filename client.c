#include "headers.h"

// #include <sys/wait.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <conio.h> //to get unbuffered input (and also doesn't work T-T)

/*
  char_check(char * paragraph, char c)
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

int random_num(){
  srand(time(NULL));
  int num = rand() % 31;
  return num;
}

char* random_paragraph(){
  char line[PAR_LEN];
  char paragraph[PAR_LEN];
  int i = 0;
  FILE *f;
  f = fopen("paragraph.txt", "r");
  int rand = random_num();
  if (f < 0){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
  printf("4\n");
  while (fgets(line, PAR_LEN, f) != NULL){
    i++;
    printf("%d\n", i);
    if (rand <= i){
      strcpy(paragraph,line);
      puts(paragraph);
    }
  }
  printf("5\n");
  /*int fd;
  FILE *f;
  char paragraph[PAR_LEN];
  int i = 0;
  int random = random_num();
  printf("%d", random);
  f = fopen("paragraph.txt", "r");
  if (f < 0){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
  while ((i < random) && (fgets(paragraph, PAR_LEN, f) != NULL)){
    fgets(paragraph, PAR_LEN, f);
    i++;
  }
  printf("hello");
  //fgets(paragraph, PAR_LEN, f);
/*  while(fgets(paragraph, sizeof(paragraph), f) != NULL){
    printf("%d\n", i);
    fgets(paragraph,PAR_LEN,f);
    paragraph_array[i] = paragraph;
    printf("Paragraph: %s", paragraph_array[i]);
    i++;
  } */
  fclose(f);
  return(paragraph);
}

int main(){
  printf("3\n");
  //======VARIABLE==DECLARATION======
  int fd;
  FILE *f;
  char* paragraph;
  char typed[PAR_LEN * 2] = "";
  char c;
  //time_t start = time(NULL);
  //=================================

/*  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return 1;
  } */
  //fgets(paragraph, PAR_LEN, f);
  printf("1\n");
  paragraph = random_paragraph();
  printf("2\n");
  paragraph[strlen(paragraph) - 1] = '\0';
  //printf("\033[2J");
  printf("'%s'\n", paragraph);
  fflush(stdout);
  while(paragraph && strcmp(paragraph, "")){
    c = getchar();
    getchar(); //"absorbs" '\n' from pressing ENTER
    if (c != '\r' && c != EOF && c != '\t'){
      strcpy(paragraph, char_check(paragraph, typed, c));
      //printf("\033[2J");
      printf("Typed: '%s' | length of typed: %ld\n\n\n", typed, strlen(typed));
      printf("'%s' | length of paragraph: %ld\n", paragraph, strlen(paragraph));
    }
    // fgets(c, 10, stdin);
    // c[strlen(c) - 1] = '\0';
    // printf("You typed: %s\n", c);
  }
  printf("Race over!\n");
  // fclose(f);
  return 0;
}
