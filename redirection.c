#include "custom_header.h"

void truncateCommand(char *cmd,int index)
{
    //truncates command as well as next index
    char ** argv = argumentize(cmd);
    int argc = argCount(argv);
    int i,n=0;
    int len=strlen(cmd);
    for(i=0;i<index;i++)
    {
        n+=strlen(argv[i]);
        n++;
    }
    int m = strlen(argv[index])+strlen(argv[index+1])+1;
    for(i=n;i<len-m;i++)
    {
        cmd[i-1]=cmd[i+m];
    }
    cmd[i]='\0';
}
char* checkInputRedirection(char *cmd)
{
    char ** argv = argumentize(cmd);
    int argc = argCount(argv);
    int i;
    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],"<"))
            break;
    }
    if(i==argc)
        return NULL;
    truncateCommand(cmd,i);
    return argv[i+1];
}

char* checkOutputRedirection(char *cmd)
{
    char ** argv = argumentize(cmd);
    int argc = argCount(argv);
    int i;
    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],">"))
            break;
    }
    if(i==argc)
        return NULL;
    truncateCommand(cmd,i);
    return argv[i+1];
}
char* checkAppendRedirection(char *cmd)
{
    char ** argv = argumentize(cmd);
    int argc = argCount(argv);
    int i;
    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],">>"))
            break;
    }
    if(i==argc)
        return NULL;
    truncateCommand(cmd,i);
    return argv[i+1];
}
