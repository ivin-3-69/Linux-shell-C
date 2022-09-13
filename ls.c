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
static int myCompare(const void *a, const void *b)
{

    // setting up rules for comparison
    return strcmp(*(const char **)a, *(const char **)b);
}
void sort(char **arr, int n)
{
    qsort(arr, n, sizeof(const char *), myCompare);
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
    int filepos = 0;
    char **arr = (char **)malloc(sizeof(char *) * 100);
    struct dirent *pDirent;
    DIR *pDir;
    if (isDir(filene) != 0)
    {
        arr[filepos] = (char *)malloc(sizeof(char) * strlen(filene) + 10);
        strcpy(arr[filepos], filene);
        filepos++;
    }
    else
    {
        pDir = opendir(filene);
        while ((pDirent = readdir(pDir)) != NULL)
        {
            if (hide == 1)
            {
                arr[filepos] = (char *)malloc(sizeof(char) * strlen(pDirent->d_name) + 10);
                strcpy(arr[filepos], pDirent->d_name);
                filepos++;
                // printf("%s\n", pDirent->d_name);
            }
            else if (hide == 0)
            {
                if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                {
                    // printf("%s\n", pDirent->d_name);
                    arr[filepos] = (char *)malloc(sizeof(char) * strlen(pDirent->d_name) + 10);
                    strcpy(arr[filepos], pDirent->d_name);
                    filepos++;
                }
            }
        }
        closedir(pDir);
    }

    sort(arr, filepos);
    int kk = 0;
    while (kk < filepos)
    {
        struct stat name;
        // if(!isDir(arr[kk])) printf("\033[1;34m%s\n", arr[kk]);
        // else if((stat(arr[kk], &name)==0) && name.st_mode & S_IXUSR) printf("\033[1;32m%s\n", arr[kk]);
        printf("%s\n", arr[kk]);
        kk++;
    }
}

void ls(char *CWD, char *HOME, char *input, char **args, int n)
{
    struct dirent *pDirent;
    const char s[] = " \"\n\t\r";
    char *token;
    char *filename;
    token = strtok(input, s);
    token = strtok(NULL, s);
    int i = 0;
    while (i < n)
    {
        if (strcmp(args[i], "-a") == 0)
            hide = 1;
        else if (strcmp(args[i], "-l") == 0)
            detail = 1;
        else if (strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0)
        {
            detail = 1;
            hide = 1;
        }
        i++;
    }
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
            {
                lsordinary(HOME);
                printf("\n");
            }
            else if (detail == 1)
            {
                lsl(HOME);
                printf("\n");
            }
        }
        else
        {
            dirr = 1;
            if (detail == 0)
            {
                lsordinary(token);
                printf("\n");
            }
            else if (detail == 1)
            {
                lsl(token);
                printf("\n");
            }
        }
        token = strtok(NULL, s);
    }
    if (dirr == 0)
    {
        if (detail == 0)
        {
            lsordinary(".");
            printf("\n");
        }
        else if (detail == 1)
        {
            lsl(".");
            printf("\n");
        }
        dirr = 1;
    }
    hide = 0;
    detail = 0;
    dirr = 0;
    return;
}