///ceaser cipher client
/*
    Written by: mhmd mhidat
*/
#include "header.h"
void decrypt (char []); //ceaser decrypt key=3
bool check_input(char []); //validate input
void make_small (char []); //make string small
void dg_cli(FILE *, int ,struct sockaddr * , socklen_t ); //client functionality
int main(int argc , char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=3)
    {
      printf("usage: client <IP_address> <port_address>\n");
      exit(0);
    }
    char por[7] = "55008";
    if (strcmp(por, argv[2]))
    {
       printf("You must use 55008 as a Port number\n");
       exit(0);
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET; //IPV4
    servaddr.sin_port=htons(atoi(argv[2])); //port is the second arg
    Inet_pton(AF_INET, argv[1],&servaddr.sin_addr); //ip is the first arg
    sockfd = Socket(AF_INET , SOCK_DGRAM,0);
    int udp_size;
    int tcp_size;
    int size=sizeof(udp_size);
    Getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &udp_size , &size);
    printf("Initial Send buf size (UDP)=%d bytes\n",udp_size);
    int tcpsock= Socket(AF_INET ,SOCK_STREAM,0); //open tcp socket to get its option.
    size=sizeof(tcp_size);
    Getsockopt(tcpsock, SOL_SOCKET, SO_RCVBUF, &tcp_size , &size);
    printf("Initial Recv buf size (TCP)=%d bytes\n",tcp_size);
    printf("Please enter new value for the send buffer, the value must be between 4608 and 425984, also must be even number\n");
    //4608 and 425984 are the deafult values for max and min size to UDP send buffer in my machine 
    int rcv,sen;
    LABLE1:
    scanf("%d",&sen);
    if(sen<4608 || sen>425984)
    {
        printf("Your value for SEND BUFFER is not in the range, try again\n");
        goto LABLE1;
    }
    if (sen % 2)
    {
        printf("Invalid Send buffer size:odd number,try again\n");
        goto LABLE1;
    }
    printf("Please enter new value for the Rcv buffer, the value must be between 4096 and 425984, also must be even number\n");
    //4096 and 425984 are the deafult values for max and min size to UDP RCV buffer in my machine 
    LABLE2:
    scanf("%d",&rcv);
    if(rcv<4096 || sen>425984)
    {
        printf("Your value for RCV BUFFER is not in the range, try again\n");
        goto LABLE2;
    }
    if (rcv % 2)
    {
        printf("Invalid RCV buffer size:odd number,try again\n");
        goto LABLE2;
    }
    sen/=2; rcv/=2;
    Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sen, sizeof(sen));
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv, sizeof(rcv));
    size=sizeof(sen);
    Getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sen , &size);
    size=sizeof(rcv);
    Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv , &size);
    printf("Modified Send buf size (UDP):%d\n",sen);
    printf("Modified Recv buf size (UDP):%d\n",rcv);
    printf("Welcome:");
    dg_cli(stdin,sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr));
    exit(0);
}
void dg_cli(FILE *fp,int sockfd, struct sockaddr * pservaddr,socklen_t servlen){
    int n;
    char arr[5]="-1"; //to check if user wants to quite
    char sendline[MAXLINE] , recvline[MAXLINE+1];
    Connect(sockfd,(struct sockaddr *)pservaddr,servlen);
    printf("Please enter a sentence to encrypt it or -1 to exit \n");
    printf("note: The message can contain only numbers and lowercase letters\n");
    char c; scanf("%c",&c);
    memset(sendline,0,strlen(sendline));
    while(Fgets(sendline,MAXLINE,fp)!=NULL)
    {   
        sendline[strlen(sendline) - 1] = '\0';
        bool flag=check_input(sendline);
        if(!strcmp(arr,sendline))
        {
            Writen(sockfd,sendline,strlen(sendline));
            printf("Bye!\n");
            exit(0);
        }
        if(!flag)
        {
            printf("Invalid input, try ageain\n");
            continue;
        }
        printf("sending %s to the server\n",sendline);
        Writen(sockfd,sendline,strlen(sendline));
        memset(recvline,0,strlen(recvline));
        n=Read(sockfd,recvline,MAXLINE);
        printf("received %s from server \n",recvline);
        recvline[n]=0;
        decrypt(recvline);
        make_small(recvline);
        printf("the received message after decryption is: %s\n",recvline);
        printf("please enter a sentence to encrypt it or -1 to exit \n");
    }
}
void decrypt(char message[MAXLINE])
{
    char ch;
    int i, key=3;
    for(i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];
        if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if(ch < 'A')
                ch = ch + 'Z' - 'A' + 1;
            message[i] = ch;
        }
        else if(ch==' ')
            continue;
        else
        {
            ch = ch - key;
            message[i] = ch;
        }
    }
}
bool check_input(char arr[MAXLINE])
{
    for(int i=0 ; i<strlen(arr);i++)
        if(! ( (arr[i] >= 97 && arr[i]<=122) || (arr[i] >= 48 && arr[i]<=57) || (arr[i]==32) ) )
            return false;
    return true;
}
void make_small (char s[]){
   for(int i=0 ;i<strlen(s);i++)
   s[i] = tolower(s[i]);
}
