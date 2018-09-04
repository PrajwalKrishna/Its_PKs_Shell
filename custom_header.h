#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<sys/utsname.h>

//Functions in argumentize.c
char ** argumentize(char * cmd);
int argCount(char ** args);

//functions in builtin_pk_ls.c
char * formatDate(char *str,time_t val);
int cmd_pk_ls(char *path);
int cmd_pk_ls_a(char *path);
int print_pk_ls_l(char *path,char *fileName);
int cmd_pk_ls_l(char *path);
int cmd_pk_ls_l_a(char *path);

//functions in exec_clock.c
int exec_clock(int interval,int times);

//functions in commandParser.c
char * parseCommand(char * cmd);

//fuctions in display.c
char * dirName();
void display();

//functions in execCmd.c
int findCmdNo(char *cmd);
int exec_pk_ls(char *cmd);
int exec_pk_pwd();
int exec_pk_cd(char *cmd);
int exec_pk_echo(char *cmd);
int exec_pk_pinfo(char *cmd);
int exec_pk_clock(char *cmd);
int launch_cmd(char *cmd);
int checkBackgroud();
int execCmd(char *cmd);

//functions in input.c
char **input();

//fuctions in lineParser.c
char ** tokanize(char * ptr);

//functions in pinfo.c
int exec_pinfo(int pid);
