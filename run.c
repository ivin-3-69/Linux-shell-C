#include "headers.h"

void run(char *CWD, char *HOME, char *instr)
{
    pid_t pid;
    FILE *fptr;
    struct stat sts;
    int backgrnd = 0;
    char *c = (char *)malloc(sizeof(char) * 2000);
    strcpy(c, instr);
    char histrorypath[2048];
    sprintf(histrorypath, "%s/history.txt", HOME);
    // printf("%s\n", histrorypath);

    FILE *fd;
    fd = fopen(histrorypath, "r");
    char buff[1024];
    fseek(fd, 0, SEEK_SET);
    int jh = 1;
    while (!feof(fd))
    {
        memset(buff, 0x00, 1024);     // clean buffer
        fscanf(fd, "%[^\n]\n", buff); // read file *prefer using fscanf
        jh++;
    }
    fclose(fd);

    // printf("%d---\n\n\n", jh);

    if (jh >= 20)
        delete (HOME);

    if (strcmp(buff, instr) != 0 || strcmp(buff, "exit") == 0)
    {
        fptr = fopen(histrorypath, "a");
        fprintf(fptr, "%s\n", instr);
        fclose(fptr);
    }

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
    int sizeoflastarg = strlen(args[n - 1]);
    if (!strcmp(args[n - 1], "&") || args[n - 1][sizeoflastarg - 1] == '&')
    {
        if (!strcmp(args[n - 1], "&"))
            args[n - 1] = NULL;
        else if (args[n - 1][sizeoflastarg - 1] == '&')
            args[n - 1][sizeoflastarg - 1] = '\0';
        backgrnd = 1;
    }
    if (strcmp(args[0], "echo") == 0)
    {
        echo(CWD, HOME, instr);
    }
    if (strcmp(args[0], "pinfo") == 0)
    {
        pinfo(CWD, HOME, instr);
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
    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "history") == 0)
    {
        FILE *fptrr;
        fptrr = fopen(histrorypath, "r");
        char lines[11][256];
        size_t i = 0;
        while (fgets(lines[i % 11], sizeof(lines[i % 11]), fptrr) != NULL)
        {
            i++;
        }
        fclose(fptrr);
        for (size_t j = i < 10 ? 0 : i - 10; j < i; j++)
        {
            fputs(lines[j % 11], stdout);
        }
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
                return;
            }
            else
            {
                return;
            }
        }
    }
}