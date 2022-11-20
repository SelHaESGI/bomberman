#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int listenfd, connfd,n;
    struct sockaddr_in serv_addr;
    uint8_t sendBuff[MAX_LINE];
    uint8_t recvBuff[MAX_LINE];

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  err_n_die("Error creating socket");
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    if(bind(listenfd,(SA*)&serv_addr, sizeof(serv_addr))<0) err_n_die("Error binding socket");
    if(listen(listenfd, 10) < 0) err_n_die("Error listening on socket");


    for(int i =0; i<5; i++){
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        printf("Waiting for connection on port %d", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd,NULL, NULL);
        printf("Connection accepted \n");

        memset(recvBuff, 0, MAX_LINE);

        while(1){
            n = recv(connfd, recvBuff, sizeof(recvBuff), 0);
            if(n == 0) break;
            printf("Received: %s \n", recvBuff);
            write(connfd, (char *)sendBuff, strlen((char *)sendBuff));
            send(connfd, recvBuff, n, 0);
        }
        close(connfd);

    }

}