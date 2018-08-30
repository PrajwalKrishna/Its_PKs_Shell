#include<string.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<errno.h>
#include<stdlib.h>

#include "display.h"

int main(int argc,char * argv[])
{
    int flag = 1;
    //intitalize
    const char *home = getenv("PWD");
    while(flag)
        display(home);
    return 0; 
}
