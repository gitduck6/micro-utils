#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int pflag = 0, vflag = 0;

    int c;
    while ((c = getopt(argc, argv, "pvm:")))
    {
        switch (c)
        {
            case 'p':
                break;
            case 'v':
                break;
            case 'm':
                break;
            default:
                fprintf(stderr, "Usage : %s -[pv] [directories]", argv[0]);
                fprintf(stderr, "Usage : %s -m [mode] [directories]", argv[0]);
                return 1;
                break;
        }
    }

    return 0;
}
