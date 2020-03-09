#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<sys/socket.h>
#include<arpa/inet.h>
 
void PKT_process(char *buffer , int size);
void Display_IP_Header(char *buffer , int size);
void Display_TCP_Header(char *buffer , int size);
 
int tcp=0,udp=0,i,j;
struct sockaddr_in source,dest;
 
int main()
{
    int saddr_size , data_size;
    struct sockaddr saddr;
    struct in_addr in;
    int raw_sock_fd;
     
    char *buffer[65536] = { 0};
     
    raw_sock_fd = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
    if(raw_sock_fd < 0)
    {
        perror("Socket Error:");
        return -1;
    }
    while(1)
    {
        saddr_size = sizeof saddr;
        data_size = recvfrom(raw_sock_fd , buffer , 65536 , 0 , &saddr , &saddr_size);
        if(data_size <0 )
        {
            perror("Recvfrom error:");
            return -1;
        }
        PKT_process(buffer , data_size);
    }
    close(raw_sock_fd);
    return 0;
}
 
void PKT_process(char* buffer, int size)
{
    struct iphdr *IPH = (struct iphdr*)buffer;
    int IPHeaderlen = IPH->ihl * 4;
    
    printf("\nReceived Packet Protocol - [%d]\n", IPH->protocol);
   
    Display_IP_Header(buffer, size);

    if( IPH->protocol == 6 ) {
            Display_TCP_Header(buffer + IPHeaderlen, size - IPHeaderlen);
    }
}
 
void Display_IP_Header(char *buffer, int Size)
{
    unsigned short iphdrlen;
         
    struct iphdr *IPH = (struct iphdr *)buffer;
    iphdrlen =IPH->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = IPH->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = IPH->daddr;
     
    printf("\nIP Header:\n");
    printf("\t\tIP Version        : %d\n",(unsigned int)IPH->version);
    printf("\t\tIP Header Length  : %d\n", iphdrlen);
    printf("\t\tIP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(IPH->tot_len));
    printf("\t\tTTL      : %d\n",(unsigned int)IPH->ttl);
    printf("\t\tProtocol : %d\n",(unsigned int)IPH->protocol);
    printf("\t\tSource IP        : %s\n",inet_ntoa(source.sin_addr));
    printf("\t\t RAW Source IP        : %d\n",IPH->saddr);
    printf("\t\tDestination IP   : %s\n",inet_ntoa(dest.sin_addr));
    printf("\n Completed IP Header\n");
}
 
void Display_TCP_Header(char* buffer, int Size)
{
    struct tcphdr *TCPH=(struct tcphdr*)buffer;
             
         
         
    printf("\n TCP Header:\n");
    printf("\t\tSource Port      : %u\n",ntohs(TCPH->source));
    printf("\t\tDestination Port : %u\n",ntohs(TCPH->dest));
    printf("\t\tSequence Number    : %u\n",ntohl(TCPH->seq));
    printf("\t\tAcknowledge Number : %u\n",ntohl(TCPH->ack_seq));
    printf("\t\tPush Flag            : %d\n",(unsigned int)TCPH->psh);
    printf("\t\tReset Flag           : %d\n",(unsigned int)TCPH->rst);
    printf("\t\tSynchronise Flag     : %d\n",(unsigned int)TCPH->syn);
    printf("\t\tFinish Flag          : %d\n",(unsigned int)TCPH->fin);
    printf("\n Completed TCP Header\n");
         
         
                         
}
 
