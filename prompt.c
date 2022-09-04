#include "headers.h"

void prompt(char *CWD, char *HOME, char *a)
{
    char *user;
    char hostbuffer[256];
    user = getlogin();
    int hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    getcwd(CWD, sizeof(CWD));

    int dirsize = strlen(CWD);
    int homesize = strlen(HOME);

    const char s[] = ";&";
    char *input;
    char input2[2048];
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
            strcpy(input2, input);
            echo(CWD, HOME, input2);
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
    // printf("%s\n%s", HOME, CWD);
    if (strcmp(HOME, CWD) == 0)
        printf("<%s@%s:~>", user, hostbuffer);
    else
        printf("<%s@%s:~%s>", user, hostbuffer, CWD);
}