#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SZIE 30

int main(int argc, const char * argv[])
{
    if(argc != 3)
    {
        printf("please input IP and port!\n");

        return 0;
    }

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(client_fd == -1)
    {
        printf("socket failure!\n");

        exit(1);
    }

    FILE * fd = fopen("file_client.txt", "wb");

    struct sockaddr_in clientaddr;

    memset(&clientaddr, 0, sizeof(clientaddr));

    clientaddr.sin_family  = AF_INET;

    clientaddr.sin_addr.s_addr = inet_addr(argv[1]);

    clientaddr.sin_port = htons(atoi(argv[2]));

    if(connect(client_fd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) == -1)
    {
        printf("connect failure!\n");

        printf("connect socket error: %s(errno: %d)\n", strerror(errno), errno);

        exit(1);
    }

    int read_len = 0;

    char buf[SZIE];

    while((read_len = read(client_fd, buf, SZIE)) != 0)
    {
        fwrite((void *)buf, 1, read_len, fd);

        //puts(buf);
    }
    
    write(client_fd, "Thank you", 10);

    puts("Received file data"); 

    fclose(fd);

    close(client_fd);

    return 0;

}