#include "headers.h"

void echo(char *CWD, char *HOME, char *input)
{
    const char s[2] = " ";
    char *token;
    token = strtok(input, s);
    while (token != NULL)
    {
        token = strtok(NULL, s);
        if(token==NULL) printf("\n");
        else printf("%s ", token);
    }
}