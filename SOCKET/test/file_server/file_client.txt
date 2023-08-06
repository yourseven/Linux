#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input port!\n");

        return 0;
    }

    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(serv_fd == -1)
    {
        printf("socket failure !\n");

        exit(1);
    }

    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servaddr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("bind failure1\n");

        exit(1);
    }

    if(listen(serv_fd, 5) == -1)
    {
        printf("listen failure!\n");

        exit(1);
    }

    int client_fd = accept(serv_fd, NULL, NULL);

    if(client_fd == -1)
    {
        printf("accept failure!\n");

        exit(1);
    }

    const unsigned char size = 30;

    int read_len = 0;

    char buf[size];

    FILE * fd = fopen("file_server.cpp", "rb");

    while (1)
    {
        read_len = fread((void *)buf, 1, size, fd);

        write(client_fd, buf, read_len);

        if(read_len < size)
        {
            fclose(fd);

            break;
        }
            
    }

    shutdown(client_fd, SHUT_WR);

    read(client_fd, buf, size);

    printf("%s\n", buf);

    close(client_fd);

    close(serv_fd);
    
    return 0;

}