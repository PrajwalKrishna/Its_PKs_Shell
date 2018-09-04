int exec_reminder(char **cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    pid_t pid,wpid;
    //background is defined when last argument is &
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
        if(check>0)
        {
            perror("It's PK's Shell");
            //If not killed multiple copies of shell would open
            _exit(1);
        }
    }
    else
    {
        //parent process for background Process
        backgroundProcess[processPointer].pid = pid;
        strcpy(backgroundProcess[processPointer].cmd,argv[0]);
        processPointer++;
        printf("%s [%d]\n",argv[0],pid);
    }
    return 0;
}
