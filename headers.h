#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <ncurses.h>
#include <sys/timeb.h>

#define PAR_LEN 800
#define FILENAME "paragraph.txt"

int random_num();
char * random_paragraph();
void print_paragraph(char * paragraph, char * typed);
char * char_check(char * paragraph, char * typed, char c);
// float get_wpm(int time, int typed);
