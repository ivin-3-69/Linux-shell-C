#include "headers.h"

void pinfo(char *HOME, char *PWD, char *input)
{
    char *token;
    char *stat;
    char *VM;
    const char ss[] = " \"\n\t\r";
    token = strtok(input, ss);
    token = strtok(NULL, ss);
    pid_t pid;

    if (token == NULL)
        pid = getpid();

    else
        pid = atoi(token);

    char status[2048];
    char exe[2048];
    char detls[1024];
    char statustemp[2048];
    char VMtemp[2048];

    sprintf(status, "/proc/%d/status", pid);
    sprintf(exe, "/proc/%d/exe", pid);

    FILE *file;
    file = fopen(status, "r");

    for (int j = 0; j < 20; j++)
    {
        fgets(detls, sizeof(detls), file);
        if (j == 2)
        {
            strcpy(statustemp, detls);
            stat = strtok(statustemp, ss);
            stat = strtok(NULL, ss);
        }
        if (j == 17)
        {
            strcpy(VMtemp, detls);
            VM = strtok(VMtemp, ss);
            VM = strtok(NULL, ss);
        }
    }
    fclose(file);

    printf("pid -- %d\nProcess Status -- %s\nVirtual Memory -- %s\nExecutable Path -- ", pid, stat, VM);
    char path[2048];
    char *ptr;
    if (readlink(exe, path, 1000))
    {
        strcat(path, "\0");
        ptr = strstr(path, HOME);
        if (ptr)
        {
            ptr += strlen(HOME);
            printf("~%s\n", ptr);
        }
        else
        {
            printf("%s\n", path);
        }
    }
    else
        printf("N/A\n"); 
}