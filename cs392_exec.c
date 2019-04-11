#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include "cs392_exec.h"

pid_t pid;
pid_t wpid;
int status;
int arg_count;

int pwd(char **args);
int ls(char **args);
// int mkdir(char **args);
// int ps(char **args);

char *builtin_str[] = {
  "pwd",
  "ls"
  // "mkdir",
  // "ps"
};

int (*builtin_func[]) (char **) = {
  &pwd,
  &ls  // &mkdir,
  // &ps
};

//built in, prints working directory
int pwd(char **args){
  char dirName[1024];
  getcwd(dirName, sizeof(dirName));
  printf("%s \n", dirName);

}

//built in, prints contents of directory
int ls(char **args){
    DIR *dir;
    struct dirent *file;
    struct stat stat;

    char buf[512];
    dir = opendir(args[1]);

    while((myfile = readdir(dir)) != NULL)
    {
        sprintf(buf, "%s/%s", args[1], file->d_name);
        stat(buf, &stat);
        printf("%zu",stat.st_size);
        printf(" %s\n", file->d_name);
    }
    closedir(dir);
}

//goes through user input and tokenizes the string returning array of strings
char ** parse(char *cmd){
    char ** tokens = malloc(sizeof(char) * 1024);
    char *token;                  //split command into separate strings
    token = strtok(cmd," ");
    char *pos;
    if ((pos=strchr(token, '\n')) != NULL)
    *pos = '\0';

    int i=0;
    while(token!=NULL){
        tokens[i]=token;      
        token = strtok(NULL," ");
        i++;
        arg_count++;
    }    
    return tokens;
}

//launches the child process that runs the command using execvp
void execute(char** cmd){
  pid = fork();

    if(pid<0){
      fprintf(stderr,"error");
    }

    if(pid == 0){
        printf("%s", cmd[0] );
        if (execvp(cmd[0], cmd) == -1) {
          perror("error");
        }
        exit(EXIT_FAILURE);
    }

    else{
      wpid = wait(NULL);
    } 
}

//called by main, starts execution process
void exec(char *cmd){
  char ** cmdarray = malloc(sizeof(char) * 1024);
  cmdarray = parse(cmd);
  if ( cmdarray[0] == NULL) {
    // An empty command was entered.
    return;
  }
  execute(cmdarray);
  free(cmdarray);
}