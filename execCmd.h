#include "argumentize.h"

const char *SUPPORTED_CMD[]={"pwd","cd","echo","exit","ls","pinfo","clock"};

#include "builtin_pk_ls.h"
#include "pinfo.h"
#include "exec_clock.h"

struct procInfo
{
  int  pid;
  char cmd[1024];
};
struct procInfo backgroundProcess[1024];
int processPointer=0;

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
        {
            free(command);
            return i;
        }
     free(command);
     return -1;
}

int exec_pk_ls(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    int aflag=0;
    int lflag=0;
    int numberOfParameter = 1;
    if(argc==1)
        return cmd_pk_ls(".");
    else if(argc==2 && argv[1][0]!='-')
        return cmd_pk_ls(argv[1]);
    if(argc>=2 && argv[1][0]=='-')
    {
        numberOfParameter++;
        if(!strcmp("-a",argv[1]))
            aflag=1;
        else if(!strcmp("-l",argv[1]))
            lflag=1;
        else if(!strcmp("-la",argv[1])||!(strcmp("-al",argv[1])))
            aflag=lflag=1;
        else
            fprintf(stderr,"%s\n","Its_PKS_Shell:Wrong flag used with ls");
    }
    if(argc>=3 && argv[2][0]=='-')
    {
        numberOfParameter++;
        if(!(strcmp("-a",argv[2])))
            aflag=1;
        else if(!(strcmp("-l",argv[2])))
            lflag=1;
        else if(!strcmp("-la",argv[2])||!(strcmp("-al",argv[2])))
            aflag=lflag=1;
        else
            fprintf(stderr,"%s\n","Its_PKS_Shell:Wrong flag used with ls");
    }
    if(numberOfParameter==argc)
    {
        if(aflag && lflag)
            return cmd_pk_ls_l_a(".");
        else if(aflag)
            return cmd_pk_ls_a(".");
        else if(lflag)
            return cmd_pk_ls_l(".");
        else
            return cmd_pk_ls(".");
    }
    int i;
    for(i=numberOfParameter;i<argc;i++)
    {
        if(aflag && lflag)
            return cmd_pk_ls_l_a(argv[i]);
        else if(aflag)
            return cmd_pk_ls_a(argv[i]);
        else if(lflag)
            return cmd_pk_ls_l(argv[i]);
        else
            return cmd_pk_ls(argv[i]);
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
int exec_pk_pinfo(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    if(argc==1)
        return exec_pinfo(0);
    else
        for(int i=1;i<argc;i++)
            exec_pinfo(atoi(argv[i]));
    return 0;
}
int exec_pk_clock(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    if(argc!=3)
    {
        fprintf(stderr,"%s\n","Its_PKS_Shell:Enter as clock -t <interval>");
        return -1;
    }
    else if(strcmp(argv[1],"-t"))
    {
        fprintf(stderr,"%s\n","Its_PKS_Shell:Enter as clock -t <interval>");
        return -1;
    }
    return exec_clock(atoi(argv[2]));
}
int launch_cmd(char *cmd)
{
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    pid_t pid,wpid;
    //background is defined when last argument is &
    int background = 0;
    if(!strcmp(argv[argc-1],"&"))
        background = 1;
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
        if(background)
            argv[argc - 1] = NULL;
        int check = execvp(argv[0],argv);
        if(check<0)
        {
            perror("It's PK's Shell");
            //If not killed multiple copies of shell would open
            _exit(1);
        }
    }
    else if(!background)
    {
        //parent Process for forground Process
        int status;
        do{
            wpid = waitpid(pid,&status,WUNTRACED);
            if(wpid<0)
            {
                perror("It's PK's Shell");
            }
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else
    {
        //parent process for background Process
        backgroundProcess[processPointer].pid = pid;
        strcpy(backgroundProcess[processPointer].cmd,argv[0]);
        processPointer++;
        int status;
        wpid = waitpid(pid,&status,WNOHANG);
        if(wpid<0)
        {
            perror("It's PK's Shell");
        }
    }
    return 0;
}
int execCmd(char *cmd)
{
    int status =0;
    int commandNumber = findCmdNo(cmd);
    if(commandNumber==-1)
    {
        status = launch_cmd(cmd);
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
            break;
        case 4:
            //ls command
            status = exec_pk_ls(cmd);
            break;
        case 5:
            //pinfo
            status = exec_pk_pinfo(cmd);
            break;
        case 6:
            //self implemented clock
            status = exec_pk_clock(cmd);
            break;
    }
    return status;
}
