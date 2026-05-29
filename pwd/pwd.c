/*\
    * Reimplementation of the unix pwd command - print working directory
    * Supported flags: -LP
    * 
    * Date: May 29 2026
    * 
    * Hello! This software intends to be simple and read understandable for the reader
    * so if any parts are too messy, PRs and issues are greatly appreciated.
    * 
    * The is rather straight forward, set the physical variable based on the flags,
    * then return a value accordingly
    * 
    * the only kinda special part of the software is the getcwd_dynamic
    * the function. I believe it has a more standart alternative called
    * get_current_dir_name(), this alternative is a GNU special function
    * 
    * since i plan to make the software as unix portable as possible 
    * i didnt include a function from a foundation literally named Gnu NOT UNIX
    * (ofc this is a joke, but adding a gnu extention makes the software less portable)
    * 
    * The functions logic is as follows:
    * do getcwd, if it fails due to the buffer being too small, make a larger buffer and try again
\*/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void usage(char * executable_name);
char *getcwd_dynamic(void);

char physical = 0;

int main(int argc, char ** argv)
{
    int c;
    while ( (c = getopt(argc,argv,"LP")) != -1)
    {
        switch (c)
        {
        case 'L':
            physical = 0;
            break;
        case 'P':
            physical = 1;
            break;
        default:
            usage(*argv);
            break;
        }
    }

    if (physical)
    {
        printf("%s\n", getcwd_dynamic());
    }
    else
    {
        printf("%s\n", getenv("PWD"));
    }

    return 0;
}

char *getcwd_dynamic(void)
{
    size_t size = 64;
    char * dirname = malloc(size);

    if (!dirname)
    {
        perror("malloc");
        exit(2);
    }

    while (getcwd(dirname,size) == NULL)
    {
        // ERANGE is set when size isnt large enough for the cwd length
        if (errno == ERANGE)
        {
            size *= 2;
            char * temp = realloc(dirname,64);
            if (!temp)
            {
                perror("malloc");
                free(dirname);
                exit(3);
            }
            dirname = temp;
        } else
        {
            perror("getcwd");
            free(dirname);
            exit(4);
        }
    }

    return dirname;
}

void usage(char * executable_name)
{
    printf("Usage: %s [-LP]\n",executable_name);
    exit(1);
}