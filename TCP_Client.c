#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 
#define MAX 1024 
#define PORT 8080
#define SA struct sockaddr 

void func(int sockfd) 
{ 
    char *buff= "10 second message\n"; 
    int n; 
    for (;;) { 
        printf("Send meddage：%s",buff); 
        n = 0; 
        write(sockfd, buff, strlen(buff)); 
        sleep(2);
    } 
} 
  
void main(int argc, char *argv[]) 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Socket created failed..\n");  
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    servaddr.sin_port = htons(PORT); 
  
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    func(sockfd); 
    close(sockfd); 
} 