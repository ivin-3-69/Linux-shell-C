#include "headers.h"
#define MAX 256
void delete (char *HOME)
{
    int lno = 1, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
    char fname[MAX];
    sprintf(fname, "%s/history.txt", HOME);
    char str[MAX], temp[] = "temp.txt";
    fptr1 = fopen(fname, "r");
    if (!fptr1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return;
    }
    fptr2 = fopen(temp, "w"); // open the temporary file in write mode
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return;
    }
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
            /* skip the line at given line number */
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname); // remove the original file
    rename(temp, fname);
}