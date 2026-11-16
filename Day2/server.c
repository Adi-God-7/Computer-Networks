#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

struct sockaddr_in serv_addr,cli_addr;
int listenfd,connfd,r,w,val,cli_addr_len,c;
unsigned short serv_port=7775;
char serv_ip[]="0.0.0.0";
char sbuff[256];
char rbuff[256];
int main(){
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(serv_port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    printf("\nTCP CHAT SERVER\n");

    listenfd=socket(AF_INET,SOCK_STREAM,0);

    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(listenfd,5);

    cli_addr_len=sizeof(cli_addr);

    printf("\nSERVER listening for clients...PRESS CTRL+C to stop echo server\n");
    connfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_addr_len);
    printf("\nClient Connected Successfully\n");

    for(;;){
        r=read(connfd,rbuff,sizeof(rbuff)-1);
        if(r<=0)
            break;
        
        rbuff[r]='\0';
        printf("\n%s\n",rbuff);
        scanf("%s",sbuff);
        
        w=write(connfd,sbuff,strlen(sbuff));
        if(w<0)
            break;
    }
    close(connfd);
    close(listenfd);
}