#include<stdio.h>


int main(void)
{
    printf("Enter a charactor :\n");
    char c = getchar();

    printf("Entered charactor is :\n");
    putchar(c);



    printf("\nEnter a different charactor :\n");
    c = fgetc(stdin);

    printf("Entered defferent charactor is :\n");
    fputc(c, stdout);

    return(0);
}