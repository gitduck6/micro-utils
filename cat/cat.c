/*
    * Reimplementation of unix cat, 
    * simple by design and my stupidity
    * 
    * Date: May 13
    * 
    * Options: -benstuv
    * Let me go over what every option does
    * n: number every line
    * b: number every non blank line, overrides  n
    * s: squeeze every repeated blank line
    * u: ignored,
    * apparently matters but gnu has it as ignores so ill do the same
    * v: shows every character in the ^M notation, for all nonprinting characters except TAB and LFD
    * t: same as v but prints TAB too
    * e: v but displays a $ at the end of each line
*/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void args(char **argv);
void fp_cat(FILE *fp);

int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0, vflag = 0;

int main(int argc,char ** argv)
{
    int c;
    while ((c = getopt(argc,argv,"benstuv")) != -1)
    {
        switch (c)
        {
        case 'b':
            bflag = 1;
            break;
        case 'e':
            eflag = 1;
            break;
        case 'n':
            nflag = 1;
            break;
        case 's':
            sflag = 1;
            break;
        case 't':
            tflag = 1;
            break;
        case 'u':
            /*gonna do nothing*/
            break;
        case 'v':
            vflag = 1;
            break;
        
        default:
            break;
        }
    }

    if (bflag) nflag = 0; // -b overwrites -n

    argv += optind;

    args(argv);

    return 0;
}


void args(char **argv)
{
    FILE * fp = stdin;
    do
    {
        if (*argv)
        {
            if (!strcmp("-",*argv)) // Unix special case for stdin
            {
                fp = stdin;
            }
            else if ((fp = fopen(*argv,"r")) == NULL)
            {
                perror("fopen");
                argv++;
                continue;
            }
        }
        else 
        {
            fp_cat(fp);
            return;
        }

        fp_cat(fp);

        if (fp != stdin)
        {
            fclose(fp);
        }
        else clearerr(fp);

        argv++;
    } while (*argv != NULL);

}

void fp_cat(FILE *fp)
{
    int prev = '\n';
    size_t line_num = 1;
    for (int c;(c = fgetc(fp)) != EOF;)
    {
        
        if (nflag)
        {
            if (prev == '\n')
            {
                printf("%6d ",line_num);
                line_num++;
            }
        }

        if (bflag)
        {
            if ((prev == '\n') && (c != '\n'))
            {
                printf("%6d ",line_num);
                line_num++;
            }
        }

        
        fputc(c,stdout);
        
        prev = c;
        
    }
    
}