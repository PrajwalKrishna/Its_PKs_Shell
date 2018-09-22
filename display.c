#include "custom_header.h"
char * dirName()
{
    char *path = (char *)malloc(1000);
    getcwd(path,1000);
    char *home = getenv("PWD");
    if(strlen(path) == strlen(home))
        return "~";
    else if(strlen(path) >= strlen(home))
    {
        char *relativePath = (char *)malloc(sizeof(path)+1);
        int lenHome = strlen(home);
        int lenPath = strlen(path);
        relativePath[0]='~';
        for(int i=lenHome;i<=lenPath;i++)
            relativePath[i-lenHome+1] = path[i];
        return relativePath;
    }
    return path;
}
void display()
{
    struct utsname userInfo;
    uname(&userInfo);
    const char *sys_name = userInfo.sysname;
    const char *user_name = getenv("USER");
    checkBackgroud();
    printf("%s@%s:",user_name,sys_name);
    printf("%s",dirName());
    printf("%c",'>');
    char ** cmd;
    cmd = input();
    for(int i=0;cmd[i]!=NULL;i++)
    {
        cmd[i]=parseCommand(cmd[i]);
        //execCmd(cmd[i]);
        pipeExec(cmd[i]);
    }
}
