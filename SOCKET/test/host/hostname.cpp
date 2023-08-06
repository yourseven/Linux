#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>


int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input IP addr!\n");

        return 0;
    }

    struct hostent * host = gethostbyname(argv[1]);

    if(host == NULL)
    {
        printf("gethostbyname error\n");

        exit(1);
    }

    printf("official name is %s\n", host->h_name);

    for(int i = 0; host->h_aliases[i]; i++)
    {
        printf("aliases%d is:%s\n", i, host->h_aliases[i]);
    }

    printf("addrtype is %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

    for(int i = 0; host->h_addr_list[i]; i++)
    {
        printf("addr%d is:%s\n", i, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    }

    return 0;
}