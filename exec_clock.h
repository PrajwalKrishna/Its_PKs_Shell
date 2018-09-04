#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int exec_clock(int interval,int times)
{
	char datePath[1024] = {"/sys/class/rtc/rtc0/date"};
	char timePath[1024] = {"/sys/class/rtc/rtc0/time"};

	char curr_date[128];
	char curr_time[128];

	pid_t pid,wpid;
	pid = fork();
	if(pid<0)
	{
		//fork error
        perror("It's PK's Shell");
        _exit(1);
	}
	else if(!pid)
	{
        int count = 0;
		while(count++ < times)
		{
			FILE *date = fopen(datePath,"r");
			if(!date)
			{
				printf("Its_PKs_Shell:Unable to open rtc log\n");
				perror("Its_PKs_Shell");
                _exit(1);
			}
			FILE *time = fopen(timePath,"r");
			if(!time)
			{
				printf("Its_PKs_Shell:Unable to open rtc log\n");
				perror("Its_PKs_Shell");
				_exit(1);
			}
			fscanf(date,"%s",curr_date);
			fscanf(time,"%s",curr_time);
			printf("%s, %s\n",curr_date,curr_time);
			fclose(date);
			fclose(time);

			//sleep
			sleep(interval);
		}
	}
	else
	{
		int status;
        do{
            wpid = waitpid(pid,&status,WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 0;
}
