const char *SUPPORTED_CMD[]={"pwd","cd","echo","ls","exit","quit"};

int findCmdNo(char *cmd)
{
    int i,n;
    n=strlen(cmd);
    int count=0;
    for(i=0;i<n;i++)
        if(cmd[i]==' ')
            break;
    count=i;
    char *command = (char *)malloc(sizeof(char)*count+2);
    for(i=0;i<count;i++)
        command[i]=cmd[i];
    command[i]='\0';
    int totalCommand = sizeof(SUPPORTED_CMD)/sizeof(char*);
    for(i=0;i<totalCommand;i++)
        if(!strcmp(command,SUPPORTED_CMD[i]))
            return i;
     return -1;
}

int exec_pk_pwd()
{
    char *path = getenv("PWD");
    printf("%s\n",path);
    return 0;
}
int exec_pk_cd(char *cmd)
{

    return 0;
}

int execCmd(char *cmd)
{
    int status =0;
    int commandNumber = findCmdNo(cmd);
    if(commandNumber==-1)
    {
        printf("error\n");
        return 0;
    }
    printf("Command number = %s\n",SUPPORTED_CMD[commandNumber]);
    switch (commandNumber)
    {
        case 0:
            //pwd command
            status = exec_pk_pwd();
            break;
        case 1:
            //cd command
            status = exec_pk_cd(cmd);
            break;
        /*case 2:
            //pwd command
            status = exec_pk_pwd(cmd);
            break;
        case 3:
            //pwd command
            status = exec_pk_pwd(cmd);
            break;
         */
    }
    return status;
}
