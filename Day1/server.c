#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

struct sockaddr_in serv_addr,cli_addr;
int listenfd,connfd,r,w;
socklen_t cli_addr_len;
unsigned short serv_port=7777;
char serv_ip[]="0.0.0.0";
char buff[128];

int main(){
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(serv_port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));
    printf("\n TCP ECHO SERVER\n");

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        printf("\nSERVER ERROR:Can't create socket\n");
        exit(1);
    }
    if(bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        printf("\nSERVER ERROR:Can't listen\n");
        close(listenfd);
        exit(1);
    }
    if(listen(listenfd,5)<0){
        printf("\nSERVER ERROR:Can't listen\n");
        close(listenfd);
        exit(1);
    }
    cli_addr_len=sizeof(cli_addr);
    printf("\nSERVER listening for clients...PRESS CTRL+C to stop echo server\n");
    connfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_addr_len);
    if(connfd<0){
        printf("\nSERVER ERROR:Can't accept connection\n");
        close(listenfd);
        exit(1);
    }
    printf("\nClient Connected Successfully\n");
    r=read(connfd,buff,127);
    if(r<0){
        printf("\nSERVER ERROR:Read Failed\n");
        close(connfd);
        close(listenfd);
        exit(1);
    }
    buff[r]='\0';
    w=write(connfd,buff,r);
    if(w<0){
        printf("\nSERVER ERROR:Can't write\n");
        close(connfd);
        close(listenfd);
        exit(1);
    }
    printf("\nSERVER ECHO BACK %s to %s \n",buff,inet_ntoa(cli_addr.sin_addr));
    close(connfd);
    close(listenfd);
    return 0;
}