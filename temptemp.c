#include "headers.h"

void prompt(char *CWD, char *HOME, char *a)
{
    const char s[] = ";&";
    char *input;
    char ch = '\0';
    input = strtok(a, s);
    while (input != NULL)
    {
        if (input[0] == 'c' && input[1] == 'd')
        {
            strncat(input, &ch, 1);
            cd(CWD, HOME, input);
        }
        else if (input[0] == 'p' && input[1] == 'w' && input[2] == 'd')
        {
            printf("%s\n", CWD);
        }
        else if (input[0] == 'e' && input[1] == 'c' && input[2] == 'h' && input[3] == 'o')
        {
            echo(CWD, HOME, input);
        }
        else if (input[0] == 'l' && input[1] == 's')
        {
            strncat(input, &ch, 1);
            ls(CWD, HOME, input);
        }
        else if (input[0] == 'p' && input[1] == 'i' && input[2] == 'n' && input[3] == 'f')
        {
            strncat(input, &ch, 1);
            pinfo(CWD, HOME, input);
        }
        input = strtok(NULL, s);
    }
}