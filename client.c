#include "headers.h"

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
  if (c == paragraph[0]){ //correctly typed
    paragraph++; //update the part to still type
    strcat(typed, &c); //update the typed part
    typed[strlen(typed) - 1] = '\0';
  }
  return paragraph;
}

void print_paragraph(char * paragraph, char * typed){
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  mvprintw(0,0,"'");
  
  //Print typed characters in Green
  attron(COLOR_PAIR(1));
  printw("%s", typed);
  attroff(COLOR_PAIR(1));

  //Print the rest of the paragraph in white
  printw("%s'\n", paragraph);
}

int random_num(){
  srand(time(NULL));
  int num = rand() % 31;
  return num;
}

void random_paragraph(){
  char **paragraphs;
  char *line;
  int i = 0;
  FILE *f;
  f = fopen("paragraph.txt", "r");
  if (f == NULL){
    printf("Error: %s\n", strerror(errno));
    return;
  }
  while(fgets(line, 10000, f)){
    fgets(line,10000,f);
    paragraphs[i] = line;
    i++;
  }
  printf("Paragraph: %s", paragraphs[random()]);
}

float get_wpm(float time){
  float seconds = time/1000;
  float wpm = 0; //final wpm
  float cpm = 60/seconds;
  wpm = cpm/5;
  
  //int words = typed/5;
  mvprintw(10,0,"seconds: %d cpm: %d wpm: %d\n", seconds,cpm, wpm);
  //float minutes = time / 60;
  //wpm = words/minutes;
  return wpm;
}

int main(){
  //variable declaration
  int fd;
  FILE *f;
  char * cur;
  char paragraph[PAR_LEN];
  char typed[PAR_LEN] = "";
  int c;
  int yMax, xMax;
  struct timeb start;
  struct timeb last;
  struct timeb new;
  start.millitm = -1;
  
  //Ncurses initialization
  initscr();
  cbreak();
  noecho();
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
  
  //Get screen size
  getmaxyx(stdscr, yMax, xMax);

  //Typing paragraph
  while (strcmp(paragraph, "\0")!= 0){
    if (start.millitm == -1){
      ftime(&start);
      ftime(&last);
    }
    print_paragraph(paragraph, typed);
    ftime(&new);
    mvprintw(yMax-1, 1, "%ld wpm\n", get_wpm(new.millitm - last.millitm));
    //printw("%s\n",paragraph);
    c = getch();
    c = (char) c;
    strcpy(paragraph, char_check(paragraph, typed, c));
    last.millitm = new.millitm;
  }
  print_paragraph(paragraph, typed);
  printw("Race Over\n");
  
  //Terminate program
  getch(); //pauses screen so it doesnt exit immediately. Press any key to exit
  endwin();
  return 0;
}
