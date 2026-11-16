#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


struct sockaddr_in serv_addr,cli_addr;
int listenfd,connfd,r;
unsigned short port=7728;
char serv_ip[]="0.0.0.0";
char sbuff[512];
char rbuff[512];

int main(){
    int num1,num2,result;
    char op;
    int cli_addr_len;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    printf("\nTCP CALCULATOR SERVER\n");

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    

    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(listenfd,5);

    printf("\nSERVER listening for clients...\n");

    while(1){
        cli_addr_len=sizeof(cli_addr);
        connfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_addr_len);

        if(connfd < 0)
            continue;

        r=read(connfd,rbuff,sizeof(rbuff)-1);
        if(r <= 0){
            close(connfd);
            continue;
        }
        rbuff[r]='\0';

        sscanf(rbuff,"%d %c %d",&num1,&op,&num2);

        if(op=='+')
            result=num1+num2;
        else if(op=='-')
            result=num1-num2;
        else if(op=='*')
            result=num1*num2;
        else if(op=='/' && num2!=0)
            result=num1/num2;
        else{
            strcpy(sbuff,"Invalid expression");
            write(connfd,sbuff,strlen(sbuff)+1);
            close(connfd);
            continue;
        }

        sprintf(sbuff,"%d",result);
        write(connfd,sbuff,strlen(sbuff)+1);

        close(connfd);
    }
}
