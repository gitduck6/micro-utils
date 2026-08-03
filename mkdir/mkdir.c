#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


static mode_t arr_to_mode(char *arr, char * status);
static inline int is_octal(char c);

int main(int argc, char ** argv)
{
    int pflag = 0, vflag = 0;
    int mode = 0755;

    int c;
    while ((c = getopt(argc, argv, "pvm:")))
    {
        switch (c)
        {
            case 'p':
                pflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            case 'm':
            {
                char status;
                mode = arr_to_mode(optarg, &status);
                if (status)
                {
                    fprintf(stderr, "Ambigious mode: %s", optarg);
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

    return 0;
}

static inline int is_octal(char c)
{
    if ((c >= '0') && (c <= '7'))
        return 1;

    return 0;
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
