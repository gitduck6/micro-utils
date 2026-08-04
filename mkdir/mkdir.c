#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


static inline int is_octal(char c);
static mode_t arr_to_mode(char *arr, char * status);
static int p_mkdir(char *directories, mode_t mode);

int main(int argc, char ** argv)
{
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
                    return 1;
                }
                break;
            }
            default:
                fprintf(stderr, "Usage : %s -[pv] [directories]\n", argv[0]);
                fprintf(stderr, "Usage : %s -[pv] -m [mode] [directories]\n", argv[0]);
                return 2;
                break;
        }
    }

    argv += optind;
    argc -= optind;

    while (*argv)
    {
        if (mkdir(*argv, mode) != 0)
        {
            perror("mkdir");
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

static int p_mkdir(char *directories, mode_t mode)
{
    char *p = directories;
    while (*p++);
    return 1;
}
