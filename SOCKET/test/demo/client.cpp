#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <string.h>



int main(int argc, const char * argv[])
{
    int mysockfd;
    struct sockaddr_in myserveraddr;
    char buf[1024];

    if((mysockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket() failed!\n");

        return -1;
    }

    memset(&myserveraddr, 0, sizeof(myserveraddr));

    myserveraddr.sin_family = AF_INET;
    myserveraddr.sin_port   = htons(atoi(argv[2]));
    myserveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    if((connect(mysockfd, (struct sockaddr *)&myserveraddr, sizeof(myserveraddr)) != 0))
    {
        printf("connect(%s, %s) failed \n", argv[1], argv[2]);

        close(mysockfd);

        return -1;
    }

    printf("connect success!\n");

    while(1)
    {
        memset(buf, 0, sizeof(buf));

        printf("please input:");

        scanf("%s", buf);

        if((write(mysockfd, buf, strlen(buf))) <= 0)
        {
            printf("write faile! \n");

            close(mysockfd);

            return -1;
        }

        memset(buf, 0, strlen(buf));

        if((read(mysockfd, buf, sizeof(buf))) <= 0)
        {
            printf("read() faile ! \n");

            close(mysockfd);

            return -1;
        }

        printf("recv: %s\n", buf);

    }
    

    return 0;
}

