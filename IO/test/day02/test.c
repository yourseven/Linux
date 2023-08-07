#include  <stdio.h>

int main(int argc, char const *argv[])
{
    FILE * fp = fopen("test.txt", "r+");

    fseek(fp, 5, SEEK_SET);

    fputc('a', fp);

    printf("%ld\n", ftell(fp));

    fseek(fp, 0, SEEK_END);

    fputs("23061", fp);

    fseek(fp, -10, SEEK_END);

    printf("%ld\n", ftell(fp));

    char buf[32] = {0};

    fgets(buf, 6, fp);

    printf("buf:%s\n", buf);

    fseek(fp, 0, SEEK_END);

    printf("%ld\n", ftell(fp));

    return 0;
}
