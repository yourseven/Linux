#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


static void Head(const char * opt, const char * filename)
{
    char * p = (char *)&opt[1];

    int rowNum = atoi(p);

    int len = 0;

    int fd = open(filename, O_RDONLY);

    if(fd < 0)
    {
        perror("open err");

        return;
    }

    char buf[32] = {0};

    while(((len = read(fd, buf, sizeof(buf))) > 0) && (rowNum > 0))
    {

        if(p = strchr(buf, '\n'))
        {
            lseek(fd, strlen(buf) - (strlen(p) - 1) - len, SEEK_CUR);

            p[1] = 0;

            write(1, buf, strlen(buf));

            rowNum--;
        }
        else write(1, buf, len);

    }

    close(fd);

}

int main(int argc, const char * argv[])
{
    Head(argv[1], argv[2]);

    return 0;
}
