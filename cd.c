#include "headers.h"

void cd(char *CWD, char *HOME, char *input)
{
    struct dirent *pDirent;
    DIR *pDir;

    const char s[2] = " ";
    char *token;
    char *filename;
    token = strtok(input, s);
    filename = strtok(NULL, s);

    if (filename == NULL)
    {
        if (chdir(HOME) != 0)
            perror("cd");
    }
    else
    {
        if (strcmp(filename, "~") == 0)
        {
            chdir(HOME);
            getcwd(CWD, 100);
        }
        else
        {
            chdir(filename);
            getcwd(CWD, 100);
        }
    }
    return;
}