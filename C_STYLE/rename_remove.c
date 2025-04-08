#include <stdio.h>


int main(void)
{
    rename("output.tex", "output.text");

    if(remove("fflush_demo.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("getchar_putchar_demo.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("input_output_redirection.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("log.txt"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("my_print_function.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("printing_all_charactor_in_file_using_cmd.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("printing_variable_argument_list.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("rename_remove.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("sscanf_demo.obj"))
    {
        printf("Error in removing file...\n");
    }

    if(remove("sscanf_demo.obj"))
    {
        printf("Error in removing file...\n");
    }




    return(0);
}