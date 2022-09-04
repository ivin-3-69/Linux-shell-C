// #include "prompt.h"
#include "headers.h"
char CWD[2048], HOME[2048], a[2048];

int main()
{
    getcwd(CWD, sizeof(CWD));
    strcpy(HOME, CWD);
    while (1)
    {
        prompt(CWD, HOME, a);
        scanf("%[^\n]%*c", a);
        int dirsize = strlen(a);
    }
}
