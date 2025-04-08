#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

void MyPrintf(char* fmt, ...);

int main(void)
{
    MyPrintf("Hi, \nMy name is %s, I am %d years old.\nMy current salary is %f%c\n", "Tushar Wagdare", 25, 50000.500, '.');


    return(0);
}

void MyPrintf(char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    vprintf(fmt, ap);

    va_end(ap);
}