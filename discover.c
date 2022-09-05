#include "headers.h"
int allfiles = 0;
int alldir = 0;
int direxist = 0;
int fileexist = 0;

int isitDir(const char *fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}

void show(char *dirname, char *filename)
{
    char **dirrrr = (char **)malloc(sizeof(char *) * 100);
    dirrrr[0] = (char *)malloc(sizeof(char) * strlen(dirname) + 10);
    strcpy(dirrrr[0], dirname);
    int i = 0;
    while (dirrrr[i] != NULL)
    {
        struct dirent *pDirent;
        DIR *pDir;
        pDir = opendir(dirrrr[i]);
        while ((pDirent = readdir(pDir)) != NULL)
        {
            printf("%s\n", pDirent->d_name);
        }
        closedir(pDir);
        printf("\n\\n\n\n");
        if (isitDir("a") == 0)
            printf("%s\n", "a");
        i++;
    }
    struct dirent *pDirent;
    DIR *pDir;
    pDir = opendir(dirname);
}

void discover(char *CWD, char *HOME, char *input, char **args, int n)
{

    const char s[] = " \"\n\t\r";
    int i = 1;
    char *dirname = (char *)malloc(sizeof(char) * 2000);
    char *filename = (char *)malloc(sizeof(char) * 2000);
    while (args[i] != NULL)
    {
        if (strcmp(args[i], "-d") == 0)
            alldir = 1;
        else if (strcmp(args[i], "-f") == 0)
            allfiles = 1;
        else if (strcmp(args[i], ".") == 0 || strcmp(args[i], "..") == 0 || strcmp(args[i], "~") == 0)
        {

            strcpy(dirname, args[i]);
            direxist = 1;
        }
        else
        {
            if (args[i][0] == '.')
            {
                strcpy(dirname, args[i]);
                direxist = 1;
            }
            else
            {
                strcpy(filename, args[i]);
                fileexist = 1;
            }
        }
        i++;
    }
    allfiles = 0;
    alldir = 0;
    char *token;
    token = strtok(input, s);
    token = strtok(NULL, s);

    if (token == NULL)
    {
        strcpy(dirname, ".");
        direxist = 1;
    }

    show(dirname, filename);
    // printf("\n directory name ");
    // printf("%s ", dirname);
    // printf("\n\n file name ");
    // printf("%s ", filename);

    return;
}