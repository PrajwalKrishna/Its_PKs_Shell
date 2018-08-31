char ** argumentize(char * cmd)
{
    int MAX_CMD = 16;
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
