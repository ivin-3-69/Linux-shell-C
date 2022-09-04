// #include "prompt.h"
#include "headers.h"
char CWD[2048], HOME[2048], a[2048];

int main()
{
    char *token;
    int pos = 0;
    char **cmd = malloc(256 * sizeof(char *));
    getcwd(CWD, sizeof(CWD));
    strcpy(HOME, CWD);
    while (1)
    {
        scanf("%[^\n]%*c", a);
        token = strtok(a, ";&");
        while (token != NULL)
        {
            cmd[pos] = token;
            pos++;
            token = strtok(NULL, ";&");
        }
        int i = 0;
        while (i < pos)
        {
            printf("%s\n", cmd[i]);
            i++;
        }
    }
}