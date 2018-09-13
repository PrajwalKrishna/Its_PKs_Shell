#include "custom_header.h"
int exec_reminder(char *cmd)
{
    pid_t pid,wpid;
    //background is defined when last argument is &
    char ** argv = argumentize(cmd);
    int argc = argCount(argv);
    int waitDuration = atoi(argv[1]);
    pid = fork();
    if(pid<0)
    {
        //fork error
        perror("It's PK's Shell");
        _exit(1);
    }
    else if(!pid)
    {
        //child process should call execvp
        int check = sleep(waitDuration);
        if(check<0)
        {
            perror("It's PK's Shell");
            //If not killed multiple copies of shell would open
            _exit(1);
        }
        printf("\nIts_PKS_Shell:\t REMINDER:");
        for(int i=2;i<argc;i++)
            printf("%s ",argv[i]);
        printf("\n");
        _exit(1);
    }
    return 0;
}
