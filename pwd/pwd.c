/*\
    * Reimplementation of the unix pwd command - print working directory
    * Supported flags: -LP
    * 
    * Date: May 29 2026
    * 
    * 
\*/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        size *= 2;
        char * temp = realloc(dirname,64);
        if (!temp)
        {
            perror("malloc");
            free(dirname);
            exit(3);
        }
        dirname = temp;
    }

    return dirname;
}

void usage(char * executable_name)
{
    printf("Usage: %s [-LP]\n",executable_name);
    exit(1);
}