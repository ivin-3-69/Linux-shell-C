#include "headers.h"
int allfiles = 0;
int alldir = 0;
int direxist = 0;
int fileexist = 0;

void show(char *dirname, char *filename)
{
    char **dirrrr = (char **)malloc(sizeof(char *) * 100);
    int dirposs = 0;
    dirrrr[dirposs] = (char *)malloc(sizeof(char) * strlen(dirname) + 10);
    char ivin[2048];
    strcpy(ivin, filename);
    strcpy(dirrrr[dirposs], dirname);
    int i = 0;
    // printf("opened directory ---- %s\n", dirrrr[0]);
    while (dirrrr[i] != NULL)
    {
        // printf("opened directory ---- %s\n", dirrrr[i]);
        struct dirent *pDirent;
        DIR *pDir;
        pDir = opendir(dirrrr[i]);
        while ((pDirent = readdir(pDir)) != NULL)
        {
            char *namename = (char *)malloc(sizeof(char) * 2000);
            sprintf(namename, "%s/%s", dirrrr[i], pDirent->d_name);
            if (opendir(namename) > 0)
            {
                if (pDirent->d_name[0] != '.')
                {
                    // printf("%s\n", namename);
                    if (alldir == 1)
                        printf("%s\n", namename);
                    dirposs++;
                    dirrrr[dirposs] = (char *)malloc(sizeof(char) * strlen(namename) + 10);
                    strcpy(dirrrr[dirposs], namename);
                }
            }
            else
            {
                if (fileexist == 1)
                {
                    // printf("kuttapan --- %s ---%s  \n", pDirent->d_name, ivin);
                    if (strcmp(pDirent->d_name, ivin) == 0)
                    {
                        printf("%s\n", namename);
                    }
                }
                else if (allfiles == 1)
                    printf("%s\n", namename);
            }
            // free(namename);
        }
        i++;
    }
    // free(dirrrr);
}

void discover(char *CWD, char *HOME, char *input, char **args, int n)
{

    const char s[] = " \"\n\t\r";
    int j = 1;
    char *dirname = (char *)malloc(sizeof(char) * 2000);
    char *filename = (char *)malloc(sizeof(char) * 2000);
    while (j < n)
    {
        if (strcmp(args[j], "-d") == 0)
            alldir = 1;
        else if (strcmp(args[j], "-f") == 0)
            allfiles = 1;
        else if (strcmp(args[j], ".") == 0 || strcmp(args[j], "..") == 0 || strcmp(args[j], "~") == 0)
        {
            strcpy(dirname, args[j]);
            direxist = 1;
        }
        else
        {
            if (args[j][0] == '.')
            {
                strcpy(dirname, args[j]);
                direxist = 1;
            }
            else
            {
                strcpy(filename, args[j]);
                fileexist = 1;
            }
        }
        j++;
    }
    // printf("the dir name is -> %s",dirname);
    // printf("the file name is -> %s",filename);

    char *token;
    token = strtok(input, s);
    token = strtok(NULL, s);

    if (token == NULL)
    {
        strcpy(dirname, ".");
        direxist = 1;
        allfiles = 1;
        alldir = 1;
    }
    if (alldir == 1 && fileexist == 0)
    {
        strcpy(dirname, ".");
    }
    if (allfiles == 0 && fileexist == 0)
    {
        allfiles = 1;
    }

    show(dirname, filename);

    allfiles = 0;
    alldir = 0;
    direxist = 0;
    fileexist = 0;
    return;
}