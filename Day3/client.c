#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

struct sockaddr_in serv_addr;
int sockfd,r;
unsigned short port=7728;
char serv_ip[]="127.0.0.1";
char sbuff[512];
char rbuff[512];

int main(){
    int ch; /* Stores one character read by getchar(). */

    /* Create the server address. */
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(serv_ip,(&serv_addr.sin_addr));

    /* Create the socket and connect to the server. */
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    /* Continue chatting until the server sends BYE. */
    while(1){
        sbuff[0]='\0';

        /* Read several lines until SEND is entered. */
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
                write(sockfd,sbuff,strlen(sbuff)+1);

                close(sockfd);

                return 0;
            }

            /* Add the line and its newline to the outgoing message. */
            strcat(sbuff,rbuff);
            strcat(sbuff,"\n");
        }

        /* Send the complete multiline message to the server. */
        write(sockfd,sbuff,strlen(sbuff)+1);

        /* Receive and display the server's reply. */
        r=read(sockfd,rbuff,sizeof(rbuff)-1);
        rbuff[r]='\0';

        puts("SERVER:");
        puts(rbuff);

        /* Stop when the server sends BYE. */
        if(strcmp(rbuff,"BYE")==0)
            break;
    }

    /* Close the socket after the chat ends. */
    close(sockfd);

    return 0;
}