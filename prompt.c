#include "headers.h"

void prompt(char *CWD, char *HOME, char *a)
{
    char *user;
    char hostbuffer[256];
    user = getlogin();
    int hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    getcwd(CWD, sizeof(CWD));

    char *token;
    int pos = 0;
    char **cmd = malloc(256 * sizeof(char *));

    token = strtok(a, ";");
    while (token != NULL)
    {
        cmd[pos] = token;
        pos++;
        token = strtok(NULL, ";");
    }
    int i = 0;
    while (i < pos)
    {
        run(CWD, HOME, cmd[i]);
        i++;
    }

    if (strcmp(HOME, CWD) == 0)
        printf("\x1B[0m<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~\x1B[0m>", user, hostbuffer);
    else
        printf("\x1B[0m<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~%s\x1B[0m>", user, hostbuffer, CWD);
}