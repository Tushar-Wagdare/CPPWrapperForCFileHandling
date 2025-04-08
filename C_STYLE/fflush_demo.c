#include <stdio.h>


int main(void)
{
    FILE* pFile = fopen("log.txt", "w");

    fprintf(pFile, "Printing to file : log.txt");
    fflush(pFile); // By flushing it ensures that the printing in the file is done immidiatlly.\

    fclose(pFile);


    return(0);
}