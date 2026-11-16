#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

struct sockaddr_in serv_addr;
int sockfd,r;
unsigned short port=7728;
char serv_ip[]="127.0.0.1";
char sbuff[512];
char rbuff[512];

int main(){
    char op;
    int ch,i;
    char first_num[64];
    char second_num[64];

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    printf("\nTCP CALCULATOR CLIENT\n");

    printf("\nEnter first number: ");
    i=0;
    while((ch=getchar())!='\n')
        first_num[i++]=(char)ch;
    first_num[i]='\0';
    while(ch != '\n')
        ch=getchar();

    printf("Enter operator (+, -, *, /): ");
    op=(char)getchar();
    while(getchar()!='\n');

    printf("Enter second number: ");
    i=0;
    while((ch=getchar())!='\n')
        second_num[i++]=(char)ch;
    second_num[i]='\0';
    while(ch != '\n')
        ch=getchar();

    sprintf(sbuff,"%s %c %s",first_num,op,second_num);

    write(sockfd,sbuff,strlen(sbuff)+1);

    r=read(sockfd,rbuff,sizeof(rbuff)-1);
    rbuff[r]='\0';

    printf("\nSERVER RESULT: %s\n",rbuff);

    close(sockfd);

    return 0;
}
