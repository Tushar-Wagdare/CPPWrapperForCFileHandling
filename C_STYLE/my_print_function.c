#include<stdio.h>
#include<stdarg.h>

void MyPrint(char* first_arg, ...);

int main(void)
{
    int age = 25;
    
    MyPrint("Hi, Age : %d, Float : %f\n", age, 2.02);

    return(0);
}

void MyPrint(char* first_arg, ...)
{
    va_list ap;
    va_start(ap, first_arg);

    for(char* ptr = first_arg; *ptr; ptr++)
    {
        if(*ptr == '%' && *(ptr + 1))
        {
            ptr++;
        
            switch(*ptr)
            {
                case 'd':
                    printf("%d", va_arg(ap, int));
                    break;

                case 'c':
                    printf("%c", (char)va_arg(ap, int));
                    break;

                case 'f':
                    printf("%f", va_arg(ap, double));
                    break;

                case 's':
                    printf("%s", va_arg(ap, char*));
                    break;
                
                case '%':   // Escape for %%
                    putchar('%');
                    break;

                default:
                    putchar('%');
                    putchar(*ptr);

            }
        }
        else
        {
            putchar(*ptr);
        }   
    }

    va_end(ap);
}
