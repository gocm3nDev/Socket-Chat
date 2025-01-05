#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 4006
#define SERVER_TLENGTH 1024

int main(){
    struct sockaddr_in clientAddr;
    int sockFD;
    char SERVER_IP[16];

    printf("\033[33mYou are communicating via port 4006.\n");

    printf("\033[33mServer IP address (xxx.xxx.xxx.xxx): ");
    fgets(SERVER_IP, sizeof(SERVER_IP), stdin);
    
    sockFD = socket(AF_INET, SOCK_STREAM, 0);

    if (sockFD < 0){
        perror("Socket error! Socket can not be created.\n");
        exit(EXIT_FAILURE);
    }

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(SERVER_PORT);
    clientAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(connect(sockFD,(struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0){
        perror("Connection error! Please try again later.\n");
        exit(EXIT_FAILURE);
    }

    printf("\033[33mConnection established as successfully!\n");

    while (1){
        char clientText[1024] = {};
        char serverResponse[1024] = {};

        printf("Write: ");
        fgets(clientText, sizeof(clientText), stdin);

        int sendByte = send(sockFD, clientText, strlen(clientText), 0);

        if (sendByte < 0)
            printf("\033[31mSend error. Sent %d byte.\n", sendByte);
        else
            printf("\033[35m(%dB)\n", sendByte);


        int recvByte = recv(sockFD, serverResponse, sizeof(serverResponse), 0);

        if (recvByte < 0) {
            printf("\033[33mReceive error.\n");
        } else if (recvByte == 0) {
            printf("\033[31mConnection closed by server.\n");
            break;
        } else {
            serverResponse[recvByte] = '\0';
            printf("\033[35mServer: %s (%dB)\n", serverResponse, recvByte);
        }

        if(strcmp(clientText, "exit") == 0){
            break;
        }
    }
    
    shutdown(sockFD, SHUT_RDWR);
    close(sockFD);
    return 0;
}
