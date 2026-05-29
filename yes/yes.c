#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[1]){
#ifdef __OpenBSD__
#include <stdlib.h>
#include <unistd.h>
  if(pledge("stdio", NULL) ==1){
    perror("pledge");
    exit(1);
  }
#endif
  if (argc < 2)
    return 0;
while (1 ==1){
  printf("%s\n", argv[1]);
}
return 0;}
