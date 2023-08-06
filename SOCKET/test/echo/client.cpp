#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, const char * argv[])
{
    if(argc != 3)
    {
        printf("please input IP and port\n");

        return 0;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if(fd == -1)
    {
        printf("socket failure!\n");

        exit(1);
    }

    struct sockaddr_in cliaddr;

    memset(&cliaddr, 0, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;

    cliaddr.sin_addr.s_addr = inet_addr(argv[1]);

    cliaddr.sin_port = htons(atoi(argv[2]));

    if(connect(fd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1)
    {
        printf("connect failure!\n");

        exit(1);
    }

    char buf[1024];

    int str_len = 0, read_len = 0, read_cnt;

    while(1)
    {
        printf("please input data to server, input \'q\' exit\n");

        gets(buf);

//        scanf("%[^\n]", buf);
 
        if(strstr(buf, "q"))
        {

            printf("exit\n");

            break;

        }

        str_len = strlen(buf) + 1;
        
        write(fd, buf, str_len);

        while(read_len < str_len)
        {
            read_cnt = read(fd, buf, sizeof(buf) - 1);

            if(read_cnt == -1)
            {
                printf("read failure!\n");

                exit(1);
            }

            read_len += read_cnt;
        }

        read_len = 0;

        printf("message from server: %s\n", buf);

        memset(buf, 0, sizeof(buf));
    }

    close(fd);

    return 0;
    
}



