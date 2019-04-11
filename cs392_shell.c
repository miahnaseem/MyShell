#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs392_exec.h"
#include "cs392_log.h"

int bufsize = 1024;

int main(){

  
  char *cmd = malloc(sizeof(char) * bufsize);
  
  //continously runs shell
  while(1){
    printf("cs392_shell$:");
    if(!fgets(cmd, bufsize, stdin)){
      fprintf(stderr,"could not get command");}

    //check if command is exit, breaks out of shell
    if(strcmp(cmd, "exit\n") == 0){            
        break;
    }
    //appends cmd to log file
    mylog(cmd);
    //starts execution process
    exec(cmd);    
  }
  free(cmd);
  return 1;
}
