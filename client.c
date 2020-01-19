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
    // printw("\n\nold paragraph: %s\n", paragraph);
    paragraph++; //update the part to still type
    // printw("\n\nnew paragraph: %s\n", paragraph);
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

char* random_paragraph(){
  //=======VARIABLE==DECLARATION=======
  char *line = malloc(sizeof(char) * PAR_LEN);
  char *paragraph = malloc(sizeof(char) * PAR_LEN);
  int i = 0;
  FILE *f;
  //===================================
  f = fopen("paragraph.txt", "r");
  int rand = random_num();
  //printf("random number: %d\n", rand);
  if (errno){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
  while (fgets(line, PAR_LEN , f) != NULL){
    if (i == rand){
      strcpy(paragraph,line);
      // puts(paragraph);
    }
    i++;
  }
  fclose(f);
  paragraph[strlen(paragraph)-1] = '\0';
  //printf("%s\n", paragraph);
  return paragraph;
}

float get_wpm(int time, int typed){
  int seconds = time;
  int cpm = typed;
  int wpm = 0;
  if (seconds != 0 && seconds < 60){
    int intervals = (int) 60/time;
    cpm= typed *intervals;
    wpm = (int)cpm/5;
  }
  else if(seconds != 0){
    cpm = (int) typed/time;
    cpm = cpm * 60;
    wpm = cpm/5;
  }
  return wpm;
}

int main(){
  //variable declaration
  int fd;
  FILE *f;
  char * cur;
  char *paragraph;
  char *update;
  char typed[PAR_LEN] = "";
  int c;
  int yMax, xMax;
  int wpm;
  int nitro = 1;
  int start = -1;
  float num_keys, errors,correct,  accuracy;
 

  //Ncurses initialization
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr,FALSE);

  //Get paragraph
  paragraph = random_paragraph();

  //Get screen size
  getmaxyx(stdscr, yMax, xMax);

  //Typing paragraph
  while (strcmp(paragraph, "\0")!= 0){
    if (start == -1){
      start= time(NULL);
    }
    print_paragraph(paragraph, typed);
    wpm = get_wpm(time(NULL)-start, strlen(typed));

    mvprintw(10, 1, "%ld wpm\n", wpm);
    c = (char) getch();
    if (c == '\r' && nitro == 1){
      while (paragraph[0] != ' '){
	      paragraph = char_check(paragraph,typed,paragraph[0]);
      }
      paragraph = char_check(paragraph,typed,paragraph[0]);
      nitro = 0;
    }
    else if (c != '\r'){
      num_keys += 1;
      update = char_check(paragraph,typed, c);
      if (strcmp(paragraph, update) == 0) {
	errors += 1;
      }
      else {
	paragraph = update;
	correct += 1;
      }
    }
    accuracy = correct / num_keys;
    mvprintw(11, 1, "Accuracy: %0.2f%\n", accuracy*100);
    mvprintw(12, 1, "Boosts: %d\n", nitro);
    wrefresh(stdscr); //clear the screen
    
  }
  print_paragraph(paragraph, typed);
  printw("Race Over\n");
  getch();
  endwin();

  return 0;

}
