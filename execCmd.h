#include "argumentize.h"

const char *SUPPORTED_CMD[]={"pwd","cd","echo","exit","ls"};

#include "builtin_pk_ls.h"

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

int exec_pk_ls(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    if(argc==1)
        return cmd_pk_ls_l(".");
    else if(argc==2)
    {
        printf("Telgu %s\n",cmd);
        int check = 0;
        extern int optind, opterr, optopt;
        extern char *optarg;
        check = getopt(argc,argv,"al");
        optind = 0;
        printf("check = %d %d\n",check,optind);
    }
    return 0;
}
int exec_pk_pwd()
{
    char *path = (char *)malloc(1000);
    getcwd(path,1000);
    printf("%s\n",path);
    free(path);
    return 0;
}
int exec_pk_cd(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    if(argc==1 || !strcmp(argv[1],"~"))
    {
        int check = chdir(getenv("PWD"));
        if(check<0)
            perror("Its_PKS_Shell");
    }
    else
    {
        int check = chdir(argv[1]);
        if(check<0)
            perror("Its_PKS_Shell");
    }
    return 0;
}
int exec_pk_echo(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    for(int i=1;i<argc;i++)
        printf("%s ",argv[i]);
    printf("\n");
    return 0;
}
int execCmd(char *cmd)
{
    int status =0;
    int commandNumber = findCmdNo(cmd);
    if(commandNumber==-1)
    {
        printf("Its_PKS_Shell:Command Not Supported\n");
        return 0;
    }
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
        case 2:
            //echo command
            status = exec_pk_echo(cmd);
            break;
        case 3:
            //exit command
            _exit(0);
        case 4:
            //ls command
            status = exec_pk_ls(cmd);
    }
    return status;
}
