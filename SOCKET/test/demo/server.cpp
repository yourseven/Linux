#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, const char ** argv)
{
    int mysocket;
    struct sockaddr_in myserveraddr;
    char buf[10];
    char ack[] = "OK\n";
    //const char addr[] = "127.0.0.1";

    if((mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("socket() faile!\n");

        return -1;
    }
    
    printf("socket success!\n");

    memset(&myserveraddr, 0, sizeof(myserveraddr));
    myserveraddr.sin_family = AF_INET;
    myserveraddr.sin_port = htons(5000);
    myserveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("addr = %d\n", myserveraddr.sin_addr.s_addr);
    int a, b;

    a = bind(mysocket, (struct sockaddr *)&myserveraddr, sizeof(myserveraddr));

    if(a < 0)
    {
        printf("bind() faile!\n");

        printf("return a = %d:\n", a);

        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);

        close(mysocket);

        return -1;
    }

    printf("bind() success!\n");

    if(listen(mysocket, 5) < 0)
    {
        printf("listen faile!\n");

        close(mysocket);

        return -1;
    }

    printf("listen() success!\n");

    if((mysocket = accept(mysocket, NULL, NULL)) < 0)
    {
        printf("accept()faile!\n");

        close(mysocket);

        return -1;
    }

    printf("accept() success!\n");

    printf("等待客户端发送消息...\n");

    memset(buf, 0, sizeof(buf));

    while(1)
    {
        b = read(mysocket, buf, sizeof(buf));

        printf("b = %d\n", b);
        
        if(b > 0)
        {
            printf("client:%s\n", buf);

            write(mysocket, ack, sizeof(ack));

            memset(buf, 0, sizeof(buf));

            printf("等待客户端发送消息...\n");
        }

        sleep(1);
    }
    

    return 0;
}