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
unsigned short serv_port=7777;
char serv_ip[]="127.0.0.1";
char rbuff[128];
char sbuff[128]="HELLO SERVER";

int main()
{
    skfd=socket(AF_INET,SOCK_STREAM,0);
    if(skfd<0)
    {
        printf("Socket creation failed\n");
        exit(1);
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(serv_port);
    serv_addr.sin_addr.s_addr=inet_addr(serv_ip);

    if(connect(skfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        printf("Connection failed\n");
        exit(1);
    }

    if(send(skfd,sbuff,strlen(sbuff),0)<0)
    {
        printf("Message sending failed\n");
        exit(1);
    }

    r=recv(skfd,rbuff,sizeof(rbuff)-1,0);
    if(r<=0)
    {
        printf("Message receiving failed\n");
        exit(1);
    }

    rbuff[r]='\0';
    printf("Server replied: %s\n",rbuff);

    close(skfd);
    return 0;
}