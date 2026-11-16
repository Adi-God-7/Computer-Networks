#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

struct sockaddr_in serv_addr;
int skfd,r,w,c;
unsigned short serv_port=7775;
char serv_ip[]="127.0.0.1";
char rbuff[256];
char sbuff[256];

int main(){
    skfd=socket(AF_INET,SOCK_STREAM,0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(serv_port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));
    printf("\nTCP CHAT CLIENT\n");
    connect(skfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    printf("\nCLIENT:Connected to the server\n");
    printf("\nSTART CHATTING\n");
    for(;;){
        scanf("%s",sbuff);
        w=write(skfd,sbuff,strlen(sbuff));
        if(w<0)
            break;
        r=read(skfd,rbuff,sizeof(rbuff)-1);
        if(r<=0)
            break;
        rbuff[r]='\0';
        printf("\n%s\n",rbuff);
    }
    close(skfd);
}