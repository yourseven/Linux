#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>


int main(int argc, const char * argv[])
{
    int state, fd;

    int recv_buf, send_buf;

    socklen_t len;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    len = sizeof(send_buf);

    state = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &send_buf, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    printf("sendbuf is %d\n", send_buf);

    len = sizeof(recv_buf);

    state = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &recv_buf, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    printf("recvbuf is %d\n", recv_buf);

    send_buf = 1024 * 4;

    recv_buf = 1024 * 4;

    state = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &send_buf, sizeof(send_buf));

    if(state)
    {
        printf("setsockopt failure!\n");

        exit(1);
    }

    state = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &recv_buf, sizeof(recv_buf));

    if(state)
    {
        printf("setockopt2 failure!\n");

        exit(1);
    }

    len = sizeof(send_buf);

    state = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &send_buf, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    len = sizeof(recv_buf);

    state = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &recv_buf, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    printf("recvbuf is %d\n", recv_buf);

    printf("sendbuf is %d\n", send_buf);

    close(fd);

    return 0;
}