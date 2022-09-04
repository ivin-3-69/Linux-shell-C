#include "headers.h"

int hide = 0;
int detail = 0;
int dirr = 0;
int isDir(const char *fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}
void lsl(char *filene)
{
    struct dirent *pDirent;
    DIR *pDir;
    if (isDir(filene) != 0)
        printf("%s\n", filene);
    else
    {
        pDir = opendir(filene);

        while ((pDirent = readdir(pDir)) != NULL)
        {
            if (hide == 1)
            {
                struct stat name;
                if (stat(filene, &name) == -1)
                {
                    perror("long_ls");
                }
                printf((pDirent->d_type == 4) ? "d" : "-");
                printf((name.st_mode & S_IRUSR) ? "r" : "-");
                printf((name.st_mode & S_IWUSR) ? "w" : "-");
                printf((name.st_mode & S_IXUSR) ? "x" : "-");
                printf((name.st_mode & S_IRGRP) ? "r" : "-");
                printf((name.st_mode & S_IWGRP) ? "w" : "-");
                printf((name.st_mode & S_IXGRP) ? "x" : "-");
                printf((name.st_mode & S_IROTH) ? "r" : "-");
                printf((name.st_mode & S_IWOTH) ? "w" : "-");
                printf((name.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", name.st_size);
                printf(" %s", pDirent->d_name);
                printf(" %s", ctime(&name.st_atime));
            }
            else if (hide == 0)
            {
                if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                {
                    struct stat name;
                    if (stat(".", &name) == -1)
                    {
                        perror("long_ls");
                    }
                    printf((pDirent->d_type == 4) ? "d" : "-");
                    printf((name.st_mode & S_IRUSR) ? "r" : "-");
                    printf((name.st_mode & S_IWUSR) ? "w" : "-");
                    printf((name.st_mode & S_IXUSR) ? "x" : "-");
                    printf((name.st_mode & S_IRGRP) ? "r" : "-");
                    printf((name.st_mode & S_IWGRP) ? "w" : "-");
                    printf((name.st_mode & S_IXGRP) ? "x" : "-");
                    printf((name.st_mode & S_IROTH) ? "r" : "-");
                    printf((name.st_mode & S_IWOTH) ? "w" : "-");
                    printf((name.st_mode & S_IXOTH) ? "x" : "-");
                    printf(" %ld", name.st_size);
                    printf(" %s", pDirent->d_name);
                    printf(" %s", ctime(&name.st_atime));
                }
            }
        }
        closedir(pDir);
    }
}
void lsordinary(char *filene)
{
    struct dirent *pDirent;
    DIR *pDir;
    if (isDir(filene) != 0)
        printf("%s\n", filene);
    else
    {
        pDir = opendir(filene);

        while ((pDirent = readdir(pDir)) != NULL)
        {
            if (hide == 1)
                printf("%s\n", pDirent->d_name);
            else if (hide == 0)
            {
                if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                    printf("%s\n", pDirent->d_name);
            }
        }
        closedir(pDir);
    }
}

void ls(char *CWD, char *HOME, char *input)
{
    struct dirent *pDirent;
    const char s[] = " \"\n\t\r";
    char *token;
    char *filename;
    token = strtok(input, s);
    token = strtok(NULL, s);
    if (token == NULL)
    {
        if (dirr == 0)
        {
            if (detail == 0)
                lsordinary(".");
            else if (detail == 1)
                lsl(".");
            dirr = 1;
        }
    }

    while (token != NULL)
    {
        if (strcmp(token, "-a") == 0)
            hide = 1;
        else if (strcmp(token, "-l") == 0)
            detail = 1;
        else if (strcmp(token, "-al") == 0 || strcmp(token, "-la") == 0)
        {
            detail = 1;
            hide = 1;
        }
        else if (strcmp(token, "~") == 0)
        {
            dirr = 1;
            if (detail == 0)
                lsordinary(HOME);
            else if (detail == 1)
                lsl(HOME);
        }
        else
        {
            dirr = 1;
            if (detail == 0)
                lsordinary(token);
            else if (detail == 1)
                lsl(token);
        }
        token = strtok(NULL, s);
    }
    if (dirr == 0)
    {
        if (detail == 0)
            lsordinary(".");
        else if (detail == 1)
            lsl(".");
        dirr = 1;
    }
    hide = 0;
    detail = 0;
    dirr = 0;
    return;
}