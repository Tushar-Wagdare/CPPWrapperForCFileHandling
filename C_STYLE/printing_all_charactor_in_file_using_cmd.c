#include<stdio.h>

int main(void)
{   
    char c;

    printf("Printing all charactors from given command line file...\n");
    while((c = getchar()) != EOF)
    {
        putchar(c);
    }

    return(0);
}