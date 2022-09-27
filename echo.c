#include "headers.h"

void echo(char *CWD, char *HOME, char *input)
{
    int printfile = 0;
    const char s[2] = " ";
    char messgae[1000] = "";
    char filename[1000] = "";
    char *token;
    token = strtok(input, s);
    while (token != NULL)
    {
        token = strtok(NULL, s);
        if (token == NULL)
        {
            if (printfile == 1)
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
                printf("%s\n", messgae);
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
                printf("%s\n", messgae);
                dup2(original, STDOUT_FILENO);
            }
            else
                printf("%s\n", messgae);
        }
        else
        {
            if (strcmp(token, ">") == 0)
                printfile = 1;
            else if (strcmp(token, ">>") == 0)
                printfile = 2;
            else
            {
                if (printfile == 0)
                    sprintf(messgae, "%s%s ", messgae, token);
                else
                {
                    strcat(filename, token);
                }
            }
        }
    }
    printfile = 0;
    strcpy(filename, "");
    strcpy(messgae, "");
    return;
}