#include "headers.h"

int hide = 0;
int detail = 0;
int printfile = 0;
char filenammmme[1000] = "";
int dirr = 0;
int isDir(const char *fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}
static int myCompare(const void *a, const void *b)
{
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
    printf("\n");
}
void lsordinary(char *filene)
{
    if (printfile == 0)
    {
        // printf("getting inside condition 0 ");
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
                }
                else if (hide == 0)
                {
                    if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                    {
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
            printf("%s\n", arr[kk]);
            kk++;
        }
        // printf("getting outside condition 0 ");
    }
    else if (printfile == 1)
    {
        printfile = 3;
        printf("getting inside condition 1 ");
        int fd2 = open(filenammmme, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd2 < 0)
        {
            perror("Failed to open file.");
            exit(1);
        }
        int original2;
        dup2(STDOUT_FILENO, original2);

        if (dup2(fd2, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            exit(1);
        }

        close(fd2);
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
                }
                else if (hide == 0)
                {
                    if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                    {
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
            printf("%s\n", arr[kk]);
            kk++;
        }
        dup2(original2, STDOUT_FILENO);
        close(original2);
        printf("getting outside condition 1 ");
        return;
    }
    else if (printfile == 2)
    {
        printfile = 3;
        printf("getting inside condition 2 ");
        int fd = open(filenammmme, O_WRONLY | O_APPEND, 0644);
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
                }
                else if (hide == 0)
                {
                    if (pDirent->d_name[0] != '.' && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
                    {
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
            printf("--->      %s\n", arr[kk]);
            kk++;
        }
        dup2(original, STDOUT_FILENO);
        close(original);
        printf("getting outside condition 2 ");
    }
    else
    {
        return;
    }
}

void ls(char *CWD, char *HOME, char *input, char **args, int n)
{
    struct dirent *pDirent;
    const char s[] = " \"\n\t\r";
    char *token;
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
        if (strcmp(token, ">") == 0)
            printfile = 1;
        else if (strcmp(token, ">>") == 0)
            printfile = 2;
        else
        {
            if (printfile == 0)
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
                    }
                    else if (detail == 1)
                    {
                        lsl(HOME);
                    }
                }
                else
                {
                    dirr = 1;
                    if (detail == 0)
                    {
                        lsordinary(token);
                    }
                    else if (detail == 1)
                    {
                        lsl(token);
                    }
                }
            }
            else
                strcat(filenammmme, token);
        }
        token = strtok(NULL, s);
    }
    if (dirr == 0)
    {
        if (detail == 0)
        {
            lsordinary(".");
        }
        else if (detail == 1)
        {
            lsl(".");
        }
        dirr = 1;
    }
    hide = 0;
    detail = 0;
    dirr = 0;
    printfile = 0;
    strcpy(filenammmme, "");
    return;
}