#include <stdio.h>
#include <string.h>

#if 0

int main(int argc, char const * argv[])
{
    if(argc != 2)
    {
        printf("please input file path\n");

        return -1;
    }
#if 0
    FILE * fp = fopen("./test.txt", "w");

    for(int i = 0; i < strlen(argv[1]); i++)

    fputc(argv[1][i], fp);

    fclose(fp);

    fp = fopen("./test.txt", "r");

    char ch;

    while((ch = fgetc(fp)) != EOF)

    printf("%c", ch);

    printf("\n");

    fclose(fp);

    //free(fp);
#endif
    FILE * fp = fopen(argv[1], "r");

    char ch;

    while((ch = fgetc(fp)) != EOF)

    printf("%c", ch);

    printf("\n");

    fclose(fp);

    return 0;
}
#endif


int main(int argc, char const *argv[])
{
    FILE * fp = fopen("./day01/", "r");

    if(fp == NULL)
    {
        printf("ERR\n");

        return -1;
    }

    char buf[30] = {0};

    while(fgets(buf, sizeof(buf) - 1, fp))

    printf("%s ", buf);

    printf("\n");

    fclose(fp);

    return 0;
}


