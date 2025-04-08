#include <iostream>
#include "file.h"


char File::s[];


void test_case_1(void);
void test_case_2(void);
void test_case_3(void);
void test_case_4(void);
void test_case_5(void);


int main(void)
{
    try
    {
        test_case_1();
        test_case_2();
        test_case_3();
        test_case_4();
        test_case_5();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return(0);
}


void test_case_1(void)
{
    puts("=============== IN test_case_1() ===============");
    puts("Just opening and closing file");
    File* fp = new File("test_case_1.txt", "w");

    delete fp;
    puts("=============== OUT test_case_1() ===============\n");
}

void test_case_2(void)
{
    puts("=============== IN test_case_2() ===============");
    puts("Creating and writing binary file");
    File* fp = new File("test_case_2.bin", "w+b");
    int arr[] = {10, 20, 30, 40, 50};
    int element_count = sizeof(arr) / sizeof(arr[0]);

    int items_written = fp->write(arr, sizeof(arr[0]), element_count);
    if(items_written == element_count)
    {
        puts("Writing binary data successfull...");
    }

    delete fp;
    puts("=============== OUT test_case_2() ===============\n");
}

void test_case_3(void)
{
    puts("=============== IN test_case_3() ===============");
    puts("Reading binary file");
    File* fp = new File("test_case_2.bin", "r+b");
    int buff[5];
    int element_count = 5;

    int items_read = fp->read(buff, sizeof(buff[0]), element_count);
    if(items_read == element_count)
    {
        puts("Reading binary data successfull...");
        for(int i = 0; i < element_count; i++)
        {
            printf("%d ", buff[i]);
        }
        puts("");
    }

    delete fp;
    puts("=============== OUT test_case_3() ===============\n");
}

void test_case_4(void)
{
    puts("=============== IN test_case_4() ===============");
    puts("File Positioning: seek, tell, rewind, getpos, setpos");
    File* fp = new File("test_case_2.bin", "r+b");
    int buff[3];
    int element_count = 3;

    long file_pointer = fp->tell();
    printf("File pointer befour seek call: %d\n", file_pointer);
    fp->seek(sizeof(int)*2, SeekOrigin::Set);
    file_pointer = fp->tell();
    printf("File pointer after seek call: %d\n", file_pointer);
    puts("Storing file position in fpos_t...");
    fpos_t pos;
    fp->get_pos(&pos);
    
    puts("Reading array(10, 20, 30, 40, 50) from 30");
    int items_read = fp->read(buff, sizeof(buff[0]), element_count);
    file_pointer = fp->tell();
    printf("File pointer after read call: %d\n", file_pointer);
    if(items_read == element_count)
    {
        puts("Reading binary data from 30 successfull...");
        for(int i = 0; i < element_count; i++)
        {
            printf("%d ", buff[i]);
        }
        puts("");
    }
    fp->rewind();
    file_pointer = fp->tell();
    printf("File pointer after rewind call: %d\n", file_pointer);

    puts("Reading array upto 3rd item after rewind");
    items_read = fp->read(buff, sizeof(buff[0]), element_count);
    file_pointer = fp->tell();
    printf("File pointer after read call: %d\n", file_pointer);
    if(items_read == element_count)
    {
        puts("Reading binary data upto 3rd item successfull...");
        for(int i = 0; i < element_count; i++)
        {
            printf("%d ", buff[i]);
        }
        puts("");
    }

    puts("Restoring file position using fpos_t...");
    fp->set_pos(&pos);
    file_pointer = fp->tell();
    printf("File pointer after set_pos call: %d\n", file_pointer);

    delete fp;
    puts("=============== OUT test_case_4() ===============\n");
}

void test_case_5(void)
{
    puts("=============== IN test_case_5() ===============");
    puts("File Operation, getchar, putchar, getstring and putstring");
    File* fp = new File("test_case_5.txt", "w");

    fp->putchar('T');
    fp->putchar('U');
    fp->putchar('S');
    fp->putchar('H');
    fp->putchar('A');
    fp->putchar('R');

    fp->putstring("\nHello\n");
    fp->putstring("Putstring demo\n");
    fp->putstring("Test case 5\n");

    fp->reopen(std::string("r"));

    char c;
    while((c = fp->getchar()) != EOF)
    {
        printf("getchar output: %c\n", c);
    }

    fp->rewind();
    char s[64];
    while(fp->getstring(s, 64) != NULL)
    {
        printf("getstring output: %s", s);
    }
        
    fp->flush();

    delete fp;
    puts("=============== OUT test_case_5() ===============\n");
}
