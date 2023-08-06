#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    int tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
    int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    int state, sock_type;

    socklen_t len = sizeof(sock_type);

    printf("TCP_FD = %d\n", SOCK_STREAM);
    printf("UDP FD = %d\n", SOCK_DGRAM);

    state = getsockopt(tcp_fd, SOL_SOCKET, SO_TYPE, &sock_type, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    printf("tcp sock type is : %d\n", sock_type);

    state = getsockopt(udp_fd, SOL_SOCKET, SO_TYPE, &sock_type, &len);

    if(state)
    {
        printf("getsockopt failure!\n");

        exit(1);
    }

    printf("udp sock type is : %d\n", sock_type);

    close(tcp_fd);

    close(udp_fd);

    return 0;


}