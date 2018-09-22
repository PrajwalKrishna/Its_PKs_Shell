#include "custom_header.h"
const int MAX_CMD = 16;
char ** argumentize(char * cmd)
{
    char *str = strdup(cmd);
    char **args = malloc(MAX_CMD * sizeof(char *));
    char *sep = " ";
    int count = 0;
    args[count++] = strtok(str,sep);
    while(args[count-1])
        args[count++] = strtok(NULL,sep);
    args[count++] = NULL;
    return args;
}
int argCount(char ** args)
{
    int count=0;
    while(args[count++]);
    count--;
    return count;
}
