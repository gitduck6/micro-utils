/*\
    * A minimal implementation of unix wc - word count
    * the flags i intend to add: -cmlwL 
    * 
\*/


#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cflag = 0;
int mflag = 0;
int lflag = 0;
int wflag = 0;
int Lflag = 0;

static int get_bytes(FILE *fd);
static int get_chars(FILE *fd);
static int get_lines(FILE *fd);
static int get_words(FILE *fd);
static int get_longest_line(FILE *fd);

int wc_handler(FILE *fd);

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

    do
    {
        FILE* fp = stdin;

        if (*argv)
        {
            if (!strcmp(*argv, "-")) // Unix special case for stdin
            {
                fp = stdin;
            }
            else
            {
                if ((fp = fopen(*argv,'r')) == NULL)
                {
                    perror(fopen);
                    argv++;
                    continue;
                }
            }
        }
        
        (void)wc_handler(fp);

        if (fp != stdin)
            fclose(fp);

        argv++;

    }
    while (*argv);
}

int wc_handler(FILE *fd)
{
    if (cflag)
    {
        get_bytes(fd);
    }

    if (mflag)
    {
        get_chars(fd);
    }

    if (lflag)
    {
        get_lines(fd);
    }

    if (wflag)
    {
        get_words(fd);
    }

    if (Lflag)
    {
        get_longest_line(fd);
    }

    return 0;
}