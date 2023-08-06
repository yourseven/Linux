#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input port!\n");

        return 0;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if(fd == -1)
    {
        printf("socket failed!\n");

        exit(1);
    }

    int opt = 1;

    socklen_t len = sizeof(opt);

    int state = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    if(state)
    {
        printf("setsockopt failure!\n");

        exit(1);
    }

    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servaddr.sin_port = htons(atoi(argv[1]));

    if(bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("bind failure!\n");

        exit(1);
    }

    if(listen(fd, 5) == -1)
    {
        printf("listen failure\n");

        exit(1);
    }

    unsigned char buf[1024];

    int client_fd, read_len;

    for(int i = 0; i < 5; i++)
    {
        client_fd = accept(fd, NULL, NULL);

        if(client_fd == -1)
        {
            printf("accept failure1\n");

            exit(1);
        }

        printf("accept success!\n");

        while((read_len = read(client_fd, buf, sizeof(buf) - 1)) != 0)
        {
            printf("client send : %s\n", buf);

            printf("read_len = %d\n", read_len);

            write(client_fd, buf, read_len);
        }

        close(client_fd);

    }

    close(fd);

    return 0;

}