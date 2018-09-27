CC=gcc

main:
	${CC} -c argumentize.c builtin_pk_ls.c commandParser.c display.c exec_clock.c execCmd.c input.c lineParser.c pinfo.c exec_reminder.c redirection.c pipe.c
	$(CC) main.c argumentize.o builtin_pk_ls.o commandParser.o display.o exec_clock.o execCmd.o input.o lineParser.o pinfo.o exec_reminder.o redirection.o pipe.o  -o ItsPKsshell

ItsPKsshell:
	${CC} -c argumentize.c builtin_pk_ls.c commandParser.c display.c exec_clock.c execCmd.c input.c lineParser.c pinfo.c exec_reminder.c redirection.c pipe.c
	$(CC) main.c argumentize.o builtin_pk_ls.o commandParser.o display.o exec_clock.o execCmd.o input.o lineParser.o pinfo.o exec_reminder.o redirection.o pipe.o  -o ItsPKsshell

clean:
	rm *.o
	rm ItsPKsshell
