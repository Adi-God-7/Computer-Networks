#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

struct sockaddr_in serv_addr,cli_addr;
int sockfd,r;
unsigned short port=7771;
char serv_ip[]="0.0.0.0";
char sbuff[128];
char rbuff[1024];

int main(){
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_port=htons(port);
        inet_aton(serv_ip,(&serv_addr.sin_addr));
        sockfd=socket(AF_INET,SOCK_STREAM,0);

        connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

        printf("Enter the command to execute on server: ");
        fgets(sbuff,sizeof(sbuff),stdin);
        sbuff[strlen(sbuff)-1]='\0';
        write(sockfd,sbuff,strlen(sbuff)+1);
        r=read(sockfd,rbuff,sizeof(rbuff)-1);
        if(r<=0){
                close(sockfd);
                return 0;
        }
        rbuff[r] = '\0';
        printf("Response from server: %s\n", rbuff);
        close(sockfd);
        return 0;
}