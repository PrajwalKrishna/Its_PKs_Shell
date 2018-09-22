#include "custom_header.h"

const int MAX_PIPE = 16;

int checkPipe(char *cmd)
{
    int n = strlen(cmd);
    for(int i=0;i<n;i++)
        if(cmd[i]=='|')
            return i;
    return -1;
}

// function for getting pipe
char ** parsePipe(char* cmd)
{
    char *str = strdup(cmd);
    char **pipelets = malloc(MAX_PIPE * sizeof(char *));
    char *sep = "|";
    int count = 0;
    pipelets[count++] = strtok(str,sep);
    while(pipelets[count-1])
        pipelets[count++] = strtok(NULL,sep);
    pipelets[count++] = NULL;
    return pipelets;
}

int pipeExec(char *cmd)
{
    //If no pipe go to execCmd.c functions
    if(checkPipe(cmd)==-1)
        return execCmd(cmd);

    char **pipelets = parsePipe(cmd);
    int pipe_num = argCount(pipelets);
    for(int i=0;i<pipe_num;i++)
        pipelets[i]=parseCommand(pipelets[i]);


    int original_stdout = dup(1);
    int original_stdin = dup(0);
    int fildes[2];

    //Cross pipe joining var
    int fd = dup(0);

    int i;
    for(i=0;i<pipe_num;i++)
    {
        if(dup2(fd,0)==-1)
            perror("Its_PKS_Shell::dup2 fail");
        close(fd);
        if(i==pipe_num-1)
        {
            if(dup2(original_stdout,1)==-1)
                perror("Its_PKS_Shell::dup2 fail");
            close(original_stdout);
        }
        else
        {
            pipe(fildes);
            fd=fildes[0];
            if(dup2(fildes[1],1)==-1)
                perror("Its_PKS_Shell::dup2 fail");
            close(fildes[1]);
        }
        int flag = execCmd(pipelets[i]);
        if(flag)
            break;
    }


    //Restore the original I\O field
    dup2(original_stdout,1);
    dup2(original_stdin,0);
    close(original_stdout);
    close(original_stdin);
    if(i!=pipe_num)
    {
        printf("Command %d not executed properly\n",i+1);
        return -1;
    }
    return 0;
}
