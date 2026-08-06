#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>


static inline int is_octal(char c);
static mode_t arr_to_mode(char *arr, char * status);
static int p_mkdir(char *path, mode_t mode);
static void usage(char *program_name);

int main(int argc, char ** argv)
{

    if (argc <= 1)
    {
        usage(argv[0]);
    }

    int pflag = 0, verbosity = 0;
    mode_t mode = 0777 & ~umask(0);

    int c;
    while ((c = getopt(argc, argv, "pvm:")) != -1)
    {
        switch (c)
        {
            case 'p':
                pflag = 1;
                break;
            case 'v':
                verbosity = 1;
                break;
            case 'm':
            {
                char status;
                mode = arr_to_mode(optarg, &status);
                if (status)
                {
                    fprintf(stderr, "Ambigious mode: %s\n", optarg);
                    return 2;
                }
                break;
            }
            default:
                usage(argv[0]);
                break;
        }
    }

    argv += optind;
    argc -= optind;

    while (*argv)
    {
        int status = (pflag) ? p_mkdir(*argv, mode) : mkdir(*argv, mode);

        if (status != 0)
        {
            perror(*argv);
        }
        else if (verbosity)
        {
            printf("created directory '%s'\n", *argv);
        }
        argv++;
    }

    return 0;
}

static inline int is_octal(char c)
{
    return (c >= '0') && (c <= '7');
}

static mode_t arr_to_mode(char *arr, char * status)
{
    mode_t mode = 0;
    while (*arr)
    {
        if (is_octal(*arr))
        {
            mode *= 8;
            mode += (*arr - '0');
        }
        else
        {
            *status = 1; // 1 status incase of fail
            return mode;
        }
        arr++;
    }

    if (mode > 0777)
        *status = 2;

    return mode;
}

static int p_mkdir(char *path, mode_t mode)
{
    char *p ;

    if (path == NULL || *path == '\0')
        return 1;

    p = path + (path[0] == '/');

    for (;*p;p++)
    {
        if (*p == '/')
        {
            *p = '\0';

            if (!mkdir(path,mode) && errno == EEXIST)
            {
                *p = '/';
                return 2;
            }

            *p = '/';
        }
    }

    if (mkdir(path, mode) == -1 && errno != EEXIST)
        return 3;

    return 0;
}

static void usage(char *program_name)
{
    fprintf(stderr, "Usage : %s -[pv] [directories]\n", program_name);
    fprintf(stderr, "Usage : %s -[pv] -m [mode] [directories]\n", program_name);
    exit(1);
}
