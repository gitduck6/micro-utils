#include <stdio.h>
#include <unistd.h>


int pflag = 0, verbosity = 0;
int main(int argc, char ** argv)
{

    int opt;
    while ((opt = getopt(argc, argv, "pv")) != -1)
    {
        switch (opt)
        {
            case 'p':
                pflag = 1;
                break;
            case 'v':
                verbosity = 1;
                break;
            default:
                fprintf(stderr, "Unknown option: \'%c\'\n", (char)opt);
                fprintf(stderr, "Usage: %s -[pv] [dir1] [dir2]\n", argv[0]);
                return 1;
                break;
        }
    }

}
