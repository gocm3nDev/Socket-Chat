#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 4006
#define SERVER_TLENGTH 1024

int main(){
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    int acceptSockFD;

    int sockFD;
    sockFD = socket(AF_INET, SOCK_STREAM, 0);

    if (sockFD < 0) {
        perror("Socket can't be created.\n");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(sockFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed\n");
        close(sockFD);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for request...");
    if(listen(sockFD, 5) < 0){
        perror("Listen unsuccesful\n");
        exit(EXIT_FAILURE);
    }

    clientAddrLen = sizeof(clientAddr);
    acceptSockFD = accept(sockFD,(struct sockaddr *)&clientAddr, &clientAddrLen);
    if(acceptSockFD < 0){
        perror("Accept error\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Connected IP: %s\nPort: %d\n",inet_ntoa(clientAddr.sin_addr), (uint16_t)ntohs(clientAddr.sin_port));


    while (1){
        char serverBUFF[1024] = {};
        char clientResponse[1024] = {};

        int recvByte = recv(acceptSockFD, serverBUFF, SERVER_TLENGTH + 1, 0);
        printf("\033[35mClient: %s (%dB)\n", serverBUFF, recvByte);

        if (recvByte < 0){
            printf("\033[33mRecieve error. Recieved %d byte.\n", recvByte);
            close(acceptSockFD);
            exit(EXIT_FAILURE);
        }
        else{
            serverBUFF[recvByte] = '\0';
        }
        
        printf("Write: ");
        fgets(clientResponse, sizeof(clientResponse), stdin);

        int sendByte = send(acceptSockFD, clientResponse, strlen(clientResponse), 0);

        if(strcmp(clientResponse, "exit") == 0) {
            break;
        }
    }

    shutdown(sockFD, SHUT_RDWR);
    close(sockFD);
    
    return 0;
}
