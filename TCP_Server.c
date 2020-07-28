#include <stdio.h> 			//standard io
#include <netdb.h> 			//servaddr
#include <unistd.h>		 	//read && write
#include <stdlib.h> 		//exit		
#include <string.h> 		//bzero
#include <sys/socket.h> 	//socket
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr 

void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, MAX); 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
		if(buff[0]==0)
			break;
        printf("Rec message：%s", buff); 
        bzero(buff, MAX); 
        n = 0; 
    } 
} 
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
	

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Socket created failed..\n"); 
    } 
    else
        printf("Socket created successfully..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    // Bind	socket
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Socket binded failed..\n"); 
    } 
    else
        printf("Socket successfully binded..\n"); 

    if ((listen(sockfd, 5)) != 0) { 
        printf("Server listening failed..\n"); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 

    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept the client failed...\n"); 
    } 
    else
        printf("server acccept the client...\n"); 
    func(connfd); 
    close(sockfd); 
} 