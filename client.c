#include "headers.h"

/*
  char_check(char * paragraph, char * typed, char c)
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





/*
  print_paragraph(char * paragraph, char * typed)
  paragraph: a pointer to the current position in the paragraph being typed
  typed: a pointer for the letters typed already

  Prints out the typed text in green and the rest of the paragraph in white.
*/
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






/*
  random_num()
  Returns a random number from 0-30
*/
int random_num(){
  srand(time(NULL));
  int num = rand() % 31;
  return num;
}






/*
  random_paragraph()
  Returns a randomly selected paragraph from paragraph.txt
*/
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






/*
  get_wpm(int time, int typed)
  time: the number of seconds since the player started typing the paragraph
  typed: the number of correctly typed characters

  Returns the words per minute statistic by calculating the number of characters typed in a minute divided by 5
*/
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






/*
  print_stats(int wpm, int boosts, int acc)
  wpm: the player's wpm
  boosts: the number of boosts the player has left
  acc: the accuracy of the player

  Displays the statistics on the user interface
*/
void print_stats(int wpm, int boosts, int acc){
  mvprintw(10, 1, "%ld wpm\n", wpm);
  mvprintw(11, 1, "Accuracy: %0.2f%\n", accuracy*100);
  mvprintw(12, 1, "Boosts: %d\n", nitro);
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
  int wpm= 0
  int nitro = 1; //number of boosts left
  int start = -1; // start time of race
  float num_keys = 0; //number of keys pressed
  float errors = 0; //number of errors made
  float accuracy = 1;

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
  while (strcmp(paragraph, "\0")!= 0){ //while there is still text left in the paragraph
    if (start == -1){ //If the race has not yet started, start the timer
      start= time(NULL);
    }

    print_paragraph(paragraph, typed);
    print_stats(wpm, nitro, accuracy);

    wpm = get_wpm(time(NULL)-start, strlen(typed));

    c = (char) getch(); //get keyboard input
    if (c == '\r' && nitro == 1){ //if player pressed enter and still has a boost
      while (paragraph[0] != ' '){ //until there is a space
	      paragraph = char_check(paragraph,typed,paragraph[0]); //move up
      }
      paragraph = char_check(paragraph,typed,paragraph[0]); //move past the space
      nitro = 0; //use the boost
    }
    else if (c != '\r'){ //if player pressed other keys
      num_keys += 1; //add to total number of keys
      update = char_check(paragraph,typed, c); //"new" paragraph
      if (strcmp(paragraph, update) == 0) { //if the "new" is the same as the original
	       errors += 1;// add 1 to the number of errors made
      }
      else {
	       paragraph = update; //else update the paragraph
      }
    }
    accuracy = (num_keys-errors) / num_keys; //calculate accuracy
    wrefresh(stdscr); //clear the screen

  }
  print_paragraph(paragraph, typed);
  printw("Race Over\n");
  getch();
  endwin();

  return 0;

}
