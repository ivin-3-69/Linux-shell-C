#include "headers.h"

void pinfo(char *HOME, char *PWD, char *input)
{
    int printfile = 0;
    char *token;
    char *stat;
    pid_t pid = getpid();
    char *VM;
    char filename[1000] = "";
    const char ss[] = " \"\n\t\r";
    token = strtok(input, ss);
    while (token != NULL)
    {
        token = strtok(NULL, ss);
        if (token != NULL)
        {
            if (strcmp(token, ">") == 0)
                printfile = 1;
            else if (strcmp(token, ">>") == 0)
                printfile = 2;
            else
            {
                if (printfile == 0)
                    pid = atoi(token);
                else
                {
                    strcat(filename, token);
                }
            }
        }
    }

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
    if (printfile == 0)
    {
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
    else if (printfile == 1)
    {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("Failed to open file.");
            exit(1);
        }
        int original;
        dup2(STDOUT_FILENO, original);

        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            exit(1);
        }

        close(fd);
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
        dup2(original, STDOUT_FILENO);
    }
    else if (printfile == 2)
    {
        int fd = open(filename, O_WRONLY | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("Failed to open file.");
            exit(1);
        }
        int original;
        dup2(STDOUT_FILENO, original);

        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            exit(1);
        }

        close(fd);
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
        dup2(original, STDOUT_FILENO);
    }
    printfile = 0;
    strcpy(filename, "");
}