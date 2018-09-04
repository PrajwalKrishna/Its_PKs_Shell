#include "custom_header.h"
char * parseCommand(char * cmd)
{
    int length = strlen(cmd);
    int i,count=0;
    //Remove trailing spaces or characters
    for(i=0;i<length;i++)
        if(!(cmd[i]==' ' || cmd[i]=='\t'))
            break;
    count+=i;
    length -= count;
    for(i=0;i<=length;i++)
        cmd[i] = cmd[i+count];
    //Remove multiple spaces(even if within "")
    char *parsed = strdup(cmd);
    int j=0;
    count=0;
    for(i=0;i<=length;i++)
        if(cmd[i]==' '|| cmd[i]=='\t')
            count++;
        else
        {
            if(count)
            {
                parsed[j++]=' ';
                count=0;
            }
            parsed[j++]=cmd[i];
        }
    return parsed;
}
