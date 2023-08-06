#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    int tcl_fd = socket(AF_INET, SOCK_STREAM, 0);

    int state, buf_send, buf_recv;

    socklen_t len = sizeof(buf_send);

    state = getsockopt(tcl_fd, SOL_SOCKET, SO_SNDBUF, &buf_send, &len);

    if(state)
    {
        printf("getsockopt 1 failure!\n");

        exit(1);
    }

    len = sizeof(buf_recv);

    state = getsockopt(tcl_fd, SOL_SOCKET, SO_RCVBUF, &buf_recv, &len);

    if(state)
    {
        printf("getsockopt 2 failure!\n");

        exit(1);
    }

    printf("send buf size is %d\n", buf_send);

    printf("recv buf size is %d\n", buf_recv);

    close(tcl_fd);

    return 0;

}