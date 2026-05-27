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

static size_t get_bytes(FILE *fd);
static size_t get_chars(FILE *fd);
static size_t get_lines(FILE *fd);
static size_t get_words(FILE *fd);
static size_t get_longest_line(FILE *fd);

int wc_handler(FILE *fd);
void usage(char* executable_name);

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
            usage(*argv);
            break;
        }
    }

    // Default options
    if (!cflag || !wflag || !lflag || !mflag || !Lflag)
    {
        cflag = wflag = lflag = 1;
    }

    argc -= optind;
    argv += optind;

    do
    {
        FILE* fp = stdin;

        if (argc == 0)
        {
            wc_handler(fp);
            break;
        }

        if (*argv)
        {
            if (!strcmp(*argv, "-")) // Unix special case for stdin
            {
                fp = stdin;
            }
            else
            {
                if ((fp = fopen(*argv,"r")) == NULL)
                {
                    perror("fopen");
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

    return 0;
}

size_t get_bytes(FILE* fd)
{
    size_t byte_count = 0;

    for (;fgetc(fd) != EOF;byte_count++);

    return byte_count;
}

size_t get_lines(FILE* fd)
{
    // ill just get this as the amount of newline characters + 1
    size_t line_count = 1;

    for (int c;(c = fgetc(fd) != EOF);)
    {
        if (c == '\n') line_count++;
    }
    return line_count;
}

int wc_handler(FILE *fd)
{
    if (cflag)
    {
        printf("%d ", get_bytes(fd));
        rewind(fd);
    }

    /*
    if (mflag)
    {
        get_chars(fd);
    }
    */

    if (lflag)
    {
        printf("%d ",get_lines(fd));
        rewind(fd);
    }

    /*
    if (wflag)
    {
        get_words(fd);
    }

    if (Lflag)
    {
        get_longest_line(fd);
    }
    */

    fputc('\n',stdout);
    return 0;
}

void usage(char* executable_name)
{
    fprintf(stderr,"Usage: %s [-cmlwL]",executable_name);
    exit(1);
}