#include <stdio.h>

int main(void)
{
    FILE* fp = fopen("log.txt", "r");
    if(NULL == fp)
    {
        perror("Error opening file...\n");
        exit(-1);
    }

    char buff[256];
    while((fgets(buff, sizeof(buff), fp)) != NULL)
    {
        fputs(buff, stderr);
    }

    if(feof(fp) != 0)
    {
        printf("File end reached...\n");
    }
    else
    {
        printf("File end not reached...\n");
    }

    if(ferror(fp) != 0)
    {
        printf("Error occured...\n");
    }
    else
    {
        printf("successfull...\n");
    }

    fclose(fp);

    return(0);
}