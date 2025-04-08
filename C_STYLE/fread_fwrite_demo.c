#include <stdio.h>

int main(void)
{
    FILE* fp = fopen("array.txt", "w+b");
    if(NULL == fp)
    {
        perror("Error creating file...\n");
        exit(-1);
    }
    else
    {
        puts("File created successfully...");
    }

    int arr[] = {10, 22, 34, 45, 56};
    size_t size = sizeof(arr[0]);
    size_t element_count = sizeof(arr)/sizeof(arr[0]);
    int buff[5];

    if(fwrite(arr, size, element_count, fp) != element_count)
    {
        if(ferror(fp) != 0)
        {
            perror("Error encountered while writing to file...\n");
            exit(-2);
        }
    }
    else
    {
        puts("Write operation on file is successfylly done...");
    }

    fflush(fp);
    rewind(fp);
    if(fread(buff, size, element_count, fp) != element_count)
    {
        if(ferror(fp) != 0)
        {
            perror("Error encountered while writing to file...\n");
            exit(-2);
        }
    }
    else
    {
        puts("Read operation on file is successfylly done...");
        puts("Array readed is :");
        for(int i = 0; i < element_count; i++)
        {
            printf("arr[%d] = %d\n", i, buff[i]);
        }
    }

    fclose(fp);

    return(0);
}