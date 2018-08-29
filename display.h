#include "input.h"

void display()
{
    struct utsname userInfo;
    uname(&userInfo);
    const char *sys_name = userInfo.sysname;
    const char *user_name = getenv("USER");
    printf("%s@%s:~",user_name,sys_name);
    //printf("%s",dirName());
    printf("%c",'>');
    char ** cmd;
    cmd = input();
    for(int i=0;cmd[i]!=NULL;i++)
        printf("%d %s\n",i+1,cmd[i]);
}
