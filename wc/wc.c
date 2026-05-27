/*\
    * A minimal implementation of unix wc - word count
    * the flags i intend to add: -cmlwL 
    * 
\*/


#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int cflag = 0;
int mflag = 0;
int lflag = 0;
int wflag = 0;
int Lflag = 0;


int wc_handler(FILE *fd, char* filename);
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
    if (!cflag && !wflag && !lflag && !mflag && !Lflag)
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
            wc_handler(fp,NULL);
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
        
        (void)wc_handler(fp,*argv);

        if (fp != stdin)
            fclose(fp);

        argv++;

    }
    while (*argv);

    return 0;
}

int wc_handler(FILE *fd, char* filename)
{   

    size_t byte_count = 0;
    size_t line_count = 1;
    size_t word_count = 0;
    size_t longest_line_length = 0;
    size_t character_count = 0;

    // Helper variables
    char previous_character = ' ';
    size_t current_line_len = 0;

    for (int c; (c = fgetc(fd))!= EOF;)
    {
        // For -c
        byte_count++;

        // For -l
        if (c == '\n') line_count++;
        
        // For -L

        if (current_line_len > longest_line_length) 
            longest_line_length = current_line_len;

        if (c == '\n')
        {
            current_line_len = 0;
        }

        // For -w
        if (isspace(previous_character) && !isspace(c)) word_count++;

        
        // ----
        current_line_len++;
        previous_character = c;
    }

    fputc(' ',stdout);

    if (cflag) printf("%d ",byte_count);
    if (lflag) printf("%d ",line_count);
    if (wflag) printf("%d ",word_count);
    if (Lflag) printf("%d ",longest_line_length);
    if (mflag) printf("%d ",character_count);

    if (filename) printf("- %s",filename);
    return 0;
}

void usage(char* executable_name)
{
    fprintf(stderr,"Usage: %s [-cmlwL]",executable_name);
    exit(1);
}