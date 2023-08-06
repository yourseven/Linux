#include <stdio.h>

int main(int argc, const char * argv[])
{
    FILE * fp = fopen("./test.txt", "a+");

    //FILE * p = fp;

    if(fp == NULL)
    {
        perror("file failed");

        return -1;
    }

    printf("FILE creat success\n");
#if 0
    for(int i = 'a'; i <= 'z'; i++)
    {
        fputc(i, fp);
    }

    if(ferror(fp))
    {
        printf("file err\n");
    }
#endif
    char a;

    while ((a = fgetc(fp)) != EOF)

    printf("%c ", a);

    printf("\n");

    fclose(fp);

    return 0;

}