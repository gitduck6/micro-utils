/*
  * uhh sorry if this code is a bit obfusc, my friend made it.
  * but it is good practice to read through cryptic code sometimes
  * it gives you pattern recognition or something
  * 
  * I mean it DOES work with the tests i did :)
  *
  * August 2 2026 : I just rewrote the whole thing
  * -n just gets rid of the trailing new line
  *
*/

#include <stdio.h> 
#include <string.h>

#ifdef __OpenBSD__
#include <stdlib.h>
#include <unistd.h>
#endif

int main(int argc, char **argv)
{
    #ifdef __OpenBSD__
    if (pledge("stdio", NULL) == 1)
    {
        perror("pledge");
        exit(1);
    }
    #endif

    char nflag = 0;
    argv++;
    if (strcmp(*argv, "-n") == 0)
    {
        nflag = 1;
        argv++;
    }

    while (*argv)
    {
        printf("%s ", *argv);
        argv++;
    }

    if (!nflag)
        fputc('\n', stdout);

    return 0;
}
