#include<string.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<errno.h>
#include<stdlib.h>

#include "display.h"

int main(int argc,char * argv[])
{
    int flag = 1;
    while(flag)
        display();
    return 0;
}
