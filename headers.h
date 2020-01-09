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
#include <time.h>

#define PAR_LEN 10
#define FILENAME "paragraph.txt"

char * char_check(char * paragraph, char c);
void random_paragraph();
