#include <stdio.h>

int main(void)
{   
    char* s = "31 March 2000";
    int day = 0, year = 0;
    char month_buff[64];

    sscanf(s, "%d %s %d", &day, month_buff, &year);

    printf("Scanned date is : %d %s %d", day, month_buff, year);

    return(0);
}