#include <stdio.h>

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input filename\n");

        return 0;
    }

    FILE * fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("file fopen failed\n");

        return -1;
    }

    char buf[1000];

    int len = 0;

    while(fgets(buf, sizeof(buf) - 1, fp)) len++;

    printf("%d ", len);

    printf("%s\n", argv[1]);

    fclose(fp);

    return 0;
}