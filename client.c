#include "headers.h"
#include "networking.h"

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
    typed[strlen(typed) - 1] = '\0'; //get rid of the extra char at end
    // printf("updated paragraph: %s\n", paragraph);
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
      puts(paragraph);
    }
    i++;
  }
  fclose(f);
  paragraph[strlen(paragraph)-1] = '\0';
  return paragraph;
}

char * strip(char * paragraph){
  char * start = paragraph;
  while ( * start == ' '){
    start ++;
  }
  char * end = paragraph;
  while (*end){
    end ++;
  }
  while (*end == ' ' || *end == '\n'){
    if (*end == '\n'){
      printf("enter\n");
    }
    if (*end == ' '){
      printf("space\n");
    }
    * end = 0;
    end --;
  }
  return start;
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

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  fd_set read_fds;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {

    printf("enter data: ");
    //the above printf does not have \n
    //flush the buffer to immediately print
    fflush(stdout);

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

  }//end loop


  //variable declaration
  int fd;
  FILE *f;
  char * cur;
  char *paragraph;
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
  paragraph = random_paragraph();
  strcat(paragraph, "\0");
  //printw("%s\n",paragraph);

  //Get screen size
  getmaxyx(stdscr, yMax, xMax);

  //Typing paragraph
  while (strcmp(paragraph, "\0")!= 0){
    mvprintw(15,0,"%s\n", paragraph);
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
    wrefresh(stdscr); //clear the screen
    last.millitm = new.millitm;

  }
  print_paragraph(paragraph, typed);
  printw("Race Over\n");
  getch();
  endwin();

  return 0;
}
