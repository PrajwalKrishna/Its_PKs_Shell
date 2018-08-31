#include<string.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

#include "display.h"

int main(int argc,char * argv[])
{
    int flag = 1;
    //intitalize
    while(flag)
        display();
    return 0;
}
