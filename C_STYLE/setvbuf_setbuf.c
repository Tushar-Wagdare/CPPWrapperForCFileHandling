#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char buff[1024];
    char c;

    FILE* pFile = fopen("out.txt", "w");
    if(NULL == pFile)
    {
        perror("Error in opening file log.txt...");
        exit(-1);
    }

    setvbuf(pFile, buff, _IOFBF, sizeof(buff));
    while((c = getchar()) != EOF)
    {
        fputc(c, pFile);
    }

    fclose(pFile);



    return(0);
}