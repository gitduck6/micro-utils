#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[1]){
if (argc < 2)
  return 0;
  
#ifdef __OpenBSD__
#include <stdlib.h>
#include <unistd.h>

  if (pledge("stdio", NULL) == 1){
    perror("pledge");
    exit(1);
  }
#endif
int a = 1;
int arg_count = argc;
  
  if (strcmp(argv[1], "-n") == 0){
    a += 1;
    while(arg_count > 2){
      printf("%s ", argv[a]);
      arg_count -= 1;
      a += 1;
  }
  }
  else{
    while(arg_count > 1){
      printf("%s ", argv[a]);
      if (arg_count == 2){
        printf("\n");
      }
      arg_count -= 1;
    a += 1;
    }
  }   
  return 0;
}
