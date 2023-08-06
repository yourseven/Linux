#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input IP addr!\n");

        return 0;
    }

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("%d\n", addr.sin_addr.s_addr);

    struct hostent * host = gethostbyaddr((void *)&addr.sin_addr.s_addr, 4, AF_INET);

    if(host == NULL)
    {
        printf("gethostbyaddr failure!\n");

        printf("errno is %d\n", errno);

        exit(1);
    }

    printf("offical name is %s:\n", host->h_name);

    for(int i = 0; host->h_aliases[i]; i++)

        printf("aliases%d is: %s\n", i, host->h_aliases[i]);

    for(int i = 0; host->h_addr_list[i]; i++)
    
        printf("addr%d is: %s\n", i, host->h_addr_list[i]);
    

    return 0;

}
