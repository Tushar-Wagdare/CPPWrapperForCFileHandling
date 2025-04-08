#include <stdio.h>

int main(void)
{
    FILE* pOutputFile = freopen("output.tex", "w", stdout);
    printf("Printing output in file...\n");
    fflush(pOutputFile);

    char str[64];
    FILE* pInputFile = freopen("log.txt", "r", stdin);
    scanf("%[^\n]", str);

    printf("Printing log.txt output in file...\n%s\n", str);
    fflush(pOutputFile);




    return(0);
}