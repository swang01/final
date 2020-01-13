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
    printw(" %s\n", paragraph);
    strcat(typed, &c); //update the typed part
    // printf("updated paragraph: %s\n", paragraph);
  }
  return paragraph;
}

int main(){
  //variable declaration
  int fd;
  FILE *f;
  char * cur;
  char paragraph[PAR_LEN];
  char typed[PAR_LEN * 2] = "";
  int c;
  int yMax, xMax;
 
  //Ncurses initialization
  initscr();
  cbreak();
  //noecho();
  nonl();
  intrflush(stdscr,FALSE);

  //Get paragraph
  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return 1;
  }
  fgets(paragraph, PAR_LEN, f);
  paragraph[strlen(paragraph) - 1] = '\0';
  printw("%s\n",paragraph);

  //Get screen size
  getmaxyx(stdscr, yMax, xMax);

  /*
  //Create new window for input
  WINDOW * inputwin = newwin(3,xMax-20,yMax-5,5);
  //box(inputwin, 0,0); //Draw a box around the input box
  refresh();
  wrefresh(inputwin);
  keypad(inputwin, TRUE);
  */
  
  //Typing paragraph
  while (strcmp(paragraph, "\0")!= 0){
    //printw("%s\n",paragraph);
    c = getch();
    strcpy(paragraph, char_check(paragraph, typed, c));
  }
  printw("Race Over\n");
  //Terminate program
  //getch(); //pauses screen so it doesnt exit immediately. Press any key to exit
  endwin();
}
