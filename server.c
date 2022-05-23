///ceaser cipher server
/*
    Written by: mhmd mhidat
*/
#include "header.h"
void dg_serv(int , struct sockaddr_in ,socklen_t);
void enc(char arr[]);
void capitlize (char []);
int main(int argc, char **argv)
{
    if(argc!=2)
    {
      printf("usage: server <port_address>\n");
      exit(0);
    }
    char por[7] = "55008";
    if (strcmp(por, argv[1]))
    {
        printf("You must use 55008 as a Port number\n");
        exit(0);
    }
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    sockfd=Socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port=htons(atoi(argv[1]));
    Bind(sockfd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
    dg_serv(sockfd,cliaddr, sizeof(cliaddr));
}
void dg_serv(int sockfd, struct sockaddr_in pcliaddr,socklen_t clilen)
{
    int n;
    socklen_t len;
    char msg [MAXLINE];
    printf("waiting for client messages......\n");
    for( ; ; )
    {
        len=clilen;
        memset(msg,0,strlen(msg));
        n=Recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr *)&pcliaddr,&len);
        char arr[10]="-1";
        if(!strcmp(msg,arr)) //if client send -1 exit
        {
            printf("received quit from client Goodbye... \n");
            exit(0);
        }
        char port[8];
        sprintf(port,"%d",ntohs(pcliaddr.sin_port));
        //print the client ip and port 
        printf("received %s from the client IP: %s Port %s \n",msg,inet_ntoa(pcliaddr.sin_addr),port);
        enc(msg); //encryption ceaser cypher with key=3
        capitlize(msg); 
        Sendto(sockfd,msg,n,0,(struct sockaddr *)&pcliaddr,len);
        printf("Sending %s to the client\n",msg);
        printf("waiting for client messages......\n");
    }
}
void enc (char message[MAXLINE])
{
    int i, key=3;
    char ch;
    for(i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];
        if(ch >= 'a' && ch <= 'z' )
        {
            ch = ch + key;
            if(ch > 'z')
                ch = ch - 'z' + 'a' - 1;
            message[i] = ch;   
        }
        else if(ch==' ')
            continue;
        else{
            message[i]+=3;
        }
    }
}
void capitlize (char s[]){
   for(int i=0 ;i<strlen(s);i++)
   s[i] = toupper(s[i]);
}