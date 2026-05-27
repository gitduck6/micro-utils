/*\
    * A minimal implementation of unix wc - word count
    * the flags i intend to add: -cmlwL 
    * 
\*/


#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cflag = 0;
int mflag = 0;
int lflag = 0;
int wflag = 0;
int Lflag = 0;

int get_bytes(FILE *fd);
int get_chars(FILE *fd);
int get_lines(FILE *fd);
int get_words(FILE *fd);
int get_longest_line(FILE *fd);

int main (int argc, char **argv)
{
    int c;
    while ((c = getopt(argc,argv,"cmlwL")) != -1)
    {
        switch (c)
        {
        case 'c':
            cflag = 1;
            break;
        case 'm':
            mflag = 1;
            break;
            
        case 'l':
            lflag = 1;
            break;
            
        case 'w':
            wflag = 1;
            break;
            
        case 'L':
            Lflag = 1;
            break;
            
        default:
            wflag = cflag = lflag = 1;
            break;
        }
    }

    argc -= optind;
    argv += optind;
}