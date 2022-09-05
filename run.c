#include "headers.h"

void run(char *CWD, char *HOME, char *instr)
{
    pid_t pid;
    struct stat sts;
    int backgrnd = 0;
    char *c = (char *)malloc(sizeof(char) * 2000);
    strcpy(c, instr);
    c = strtok(c, " \n\t\r");

    char **args = (char **)malloc(sizeof(char *) * 100);
    int n = 0;
    while (c != NULL)
    {
        args[n] = (char *)malloc(sizeof(char) * strlen(c) + 10);
        strcpy(args[n], c);
        c = strtok(NULL, " \n\t\r");
        n++;
    }
    int i = 0;
    if (!strcmp(args[n - 1], "&"))
    {
        args[n - 1] = NULL;
        backgrnd = 1;
    }
    if (strcmp(args[0], "echo") == 0)
    {
        echo(CWD, HOME, instr);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        printf("%s\n", CWD);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        cd(CWD, HOME, instr);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        ls(CWD, HOME, instr, args, n);
    }
    else if (strcmp(args[0], "discover") == 0)
    {
        discover(CWD, HOME, instr, args, n);
    }
    else
    {
        pid = fork();
        char status[2048];
        sprintf(status, "/proc/%d", pid);
        if (pid == 0)
        {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        else
        {
            if (!backgrnd)
            {
                wait(NULL);
            }
        }
    }
}