/*\
    * Reimplementation of the unix pwd command - print working directory
    * Supported flags: -LP
    * 
    * Date: May 29 2026
\*/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char * executable_name);

char physical = 0;

int main(int argc, char ** argv)
{
    int c;
    while ( (c = getopt(argc,argv,"LP")) != -1)
    {switch (c)
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
    }}
}

void usage(char * executable_name)
{
    printf("Usage: %s [-LP]\n",executable_name)
}