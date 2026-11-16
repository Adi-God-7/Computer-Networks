#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

struct sockaddr_in serv_addr,cli_addr;
int listenfd,connfd;
int r;
unsigned short port=7771;
char serv_ip[]="127.0.0.1";
char sbuff[1024];
char rbuff[1024];
char buff2[1024];

FILE *fp;
int main(){
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(listenfd,5);

    int cli_addr_len=sizeof(cli_addr);
    connfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_addr_len);

    r=read(connfd,rbuff,sizeof(rbuff)-1);
    if(r <= 0){
        close(connfd);
        return 0;
    }
    rbuff[r] = '\0';
    strcat(rbuff,"> xyz.txt");
    system(rbuff);
    fp=fopen("xyz.txt","a+");
    sbuff[0] = '\0';
    while(fgets(buff2,sizeof(buff2),fp)!=NULL){
        strcat(sbuff,buff2);
    }
    fclose(fp);
    write(connfd,sbuff,sizeof(sbuff));
    close(connfd);
    return 0;
}