#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

struct sockaddr_in serv_addr,cli_addr;
int listenfd,connfd,r;
unsigned short port=7728;
char serv_ip[]="0.0.0.0";
char sbuff[512];
char rbuff[512];

int main(){
    int ch; /* Stores one character read by getchar(). */

    /* Create the server socket address. */
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    /* Create the socket and wait for a client connection. */
    listenfd=socket(AF_INET,SOCK_STREAM,0);

    printf("\nTCP CHAT SERVER\n");

    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(listenfd,5);

    int cli_addr_len=sizeof(cli_addr);
    connfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_addr_len);

    /* Continue chatting until the client sends BYE. */
    while(1){
        r=read(connfd,rbuff,sizeof(rbuff)-1);
        rbuff[r]='\0';

        puts("CLIENT:");
        puts(rbuff);

        if(strcmp(rbuff,"BYE")==0)
            break;

        /* Read several lines until SEND is entered. */
        sbuff[0]='\0';

        puts("Enter message (type SEND on a separate line):");

        while(1){
            int i=0; /* Position of the next character in rbuff. */

            /*
             * getchar() reads one character at a time.
             * Keep reading until the user presses Enter ('\n').
             */
            while((ch=getchar())!='\n')
                rbuff[i++]=(char)ch;

            /* End the text so rbuff can be used as a string. */
            rbuff[i]='\0';

            /* SEND ends the current multiline message. */
            if(strcmp(rbuff,"SEND")==0)
                break;

            /* BYE ends the chat immediately. */
            if(strcmp(rbuff,"BYE")==0){
                strcat(sbuff,"BYE");
                write(connfd,sbuff,strlen(sbuff)+1);

                close(connfd);
                close(listenfd);

                return 0;
            }

            /* Add the line and its newline to the outgoing message. */
            strcat(sbuff,rbuff);
            strcat(sbuff,"\n");
        }

        /* Send the complete multiline message to the client. */
        write(connfd,sbuff,strlen(sbuff)+1);
    }

    /* Close both sockets after the chat ends. */
    close(connfd);
    close(listenfd);

    return 0;
} 