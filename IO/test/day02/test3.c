#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);

    if(fd < 0)
    {
        perror("open err");

        return 0;
    }

    write(fd, "hello", 5);

    char buf[32] = {0};

    lseek(fd, 0, SEEK_SET);

    printf("len = %d\n", read(fd, buf, sizeof(buf)));

    printf("buf = %s\n", buf);

    close(fd);

    write(1, buf, 32);

    return 0;
}
