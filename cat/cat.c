/*
    * Reimplementation of unix cat, 
    * simple by design and my stupidity
    * 
    * Date: May 13
    * 
    * Options: -benstuv
    * Let me go over what every option does
    * b: number every non blank line
    * n: number every line
    * s: squeeze every repeated blank line
    * u: (ignored)
    * v: shows every character in the ^M notation, for all nonprinting characters except TAB and LFD
    * t: same as v but prints TAB too
    * e: v but displays a $ at the end of each line
*/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char ** argv)
{
    int c;
    while ((c = getopt(argc,argv,"benstuv")) != -1)
    {
        switch (c)
        {
        case 'b':
            break;
        case 'e':
            break;
        case 'n':
            break;
        case 's':
            break;
        case 't':
            break;
        case 'u':
            break;
        case 'v':
            break;
        
        default:
            break;
        }
    }

    return 0;
}