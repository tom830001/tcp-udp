#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define MYPORT 8080
#define ERR_EXIT(m) \
    do { \
    perror(m); \
    exit(EXIT_FAILURE); \
    } while (0)
//char* SERVERIP = "192.168.125.126";

void echo_cli(int sock, char *argv[])
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    int ret;
    char *sendbuf = "10 second message";
    char recvbuf[1024] = {0};
    while (1)
    {
        
        printf("Send meddage：%s\n",sendbuf);
        sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		sleep(10);
    }
    
    close(sock);
    
    
}

void main(int argc, char *argv[])
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        ERR_EXIT("socket");
    
    echo_cli(sock, argv);
    
}