#include <stdio.h>

#ifdef __OpenBSD__
#include <stdlib.h>
#include <unistd.h>
#endif

int main(int argc, char **argv)
{
#ifdef __OpenBSD__
    if(pledge("stdio", NULL) ==1)
    {
        perror("pledge");
        exit(1);
    }
#endif

    char * word;

    if (argc < 2)
        word = "y";
    else word = argv[1];

    while (1) // while (1 == 1) ts aint rust my guy
    {
        printf("%s\n", word);
    }
    return 0;
}
