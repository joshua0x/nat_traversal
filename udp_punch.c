#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>

#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(1);\
    }while(0)

#define  ID_BYTE_SIZE  10 
#define  LISTEN_PORT   8888
typedef struct{
    struct in_addr ip;
    int port;
}peerInfo;
int main()
{
    peerInfo info[2];
    unsigned char str[10] = {0};
 
    /* udp socket */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        ERR_EXIT("SOCKET");
 
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serveraddr.sin_port = htons(LISTEN_PORT);
    serveraddr.sin_family = AF_INET;    
 
    int ret = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1)
        ERR_EXIT("BIND");
 
    while(1)
    {
        bzero(info, sizeof(peerInfo)*2);
        socklen_t addrlen = sizeof(struct sockaddr_in);
        /* recvfrom(sockfd, &ch, sizeof(ch), 0, (struct sockaddr *)&serveraddr, &addrlen); */
        recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&serveraddr, &addrlen);
        
        memcpy(&info[0].ip, &serveraddr.sin_addr, sizeof(struct in_addr));
        info[0].port = serveraddr.sin_port;
 
        printf("A client IP:%s \tPort:%d peer0  query!\n", inet_ntoa(info[0].ip), ntohs(info[0].port));
 
        /* recvfrom(sockfd, &ch, sizeof(ch), 0, (struct sockaddr *)&serveraddr, &addrlen); */
        recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&serveraddr, &addrlen);
        memcpy(&info[1].ip, &serveraddr.sin_addr, sizeof(struct in_addr));
        info[1].port = serveraddr.sin_port;
 
        printf("B client IP:%s \tPort:%d peer1  query!\n", inet_ntoa(info[1].ip), ntohs(info[1].port));
 
        printf("send peer  endpoint address...\n");
        serveraddr.sin_addr = info[0].ip;
        serveraddr.sin_port = info[0].port;
        sendto(sockfd, &info[1], sizeof(peerInfo), 0, (struct sockaddr *)&serveraddr, addrlen);
 
        serveraddr.sin_addr = info[1].ip;
        serveraddr.sin_port = info[1].port;
        sendto(sockfd, &info[0], sizeof(peerInfo), 0, (struct sockaddr *)&serveraddr, addrlen);
        printf("send done!\n");
    }
    return 0;
}
