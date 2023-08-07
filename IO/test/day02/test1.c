#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int  main(int argc, const char * argv[])
{
    int fd = open(argv[1], O_RDONLY);

    if(fd < 0)
    {
        perror("open err\n");

        return -1;
    }

    int fd1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);

    if(fd1 < 0)
    {
        perror("open err\n");

        exit(1);
    }

    char buf[32] = {0};

    int len;

    while((len = read(fd, buf, sizeof(buf))) > 0)

    write(fd1, buf, len);

    close(fd);

    close(fd1);

    return 0;
}