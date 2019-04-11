#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cs392_log.h"

//takes user input and appends it to file cs392_shell.log
void mylog(char *cmd){
  FILE *fp;
  fp = fopen("cs392_shell.log", "a");

  if (fp == NULL){ 
        puts("Couldn't open file"); 
        exit(0); 
    } 

    fwrite(cmd, sizeof(char), sizeof(cmd), fp);

    fclose(fp); 
    
    return ;
};
