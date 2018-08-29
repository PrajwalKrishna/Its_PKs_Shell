char ** tokanize(char * ptr)
{
    int MAX_CMD = 16;
    char *tok;
    char *str = strdup(ptr);
    char **cmd = malloc(MAX_CMD * sizeof(char *));
    char *sep = ";\n";
    int count = 0;
    cmd[count++] = strtok(str,sep);
    while(cmd[count-1])
    {
        cmd[count++] = strtok(NULL,sep);
    }
    cmd[count++] = NULL;
    return cmd;
}
