#include <stdio.h>
#include <unistd.h>

int p_rmdir(char * pathname);

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
                fprintf(stderr, "Usage: %s -[pv] [dir1] [dir2] ...\n", argv[0]);
                return 1;
                break;
        }
    }

    argv += optind;
    argc -= optind;

    while (*argv)
    {

        int status = (pflag) ? p_rmdir(*argv) : rmdir(*argv);

        if (verbosity && (status == 0))
        {
            printf("rmdir: %s created.\n", *argv);
        }
        if (status != 0)
        {
            perror("rmdir");
        }

        argv++;
    }


    return 0;
}

int p_rmdir(char * pathname)
{
    char * last_slash = pathname;

    while (*last_slash)
        last_slash++;

    while (1)
    {
        *last_slash = '\0';
        if (rmdir(pathname) != 0)
            return 1;
        *last_slash = '/';

        while ((pathname < last_slash) && (*last_slash != '/'))
            last_slash--;

        if (pathname > last_slash)
            break;

        if (pathname == last_slash)
            break;
    }

    return 0;
}
