// Client Side Code
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
  
#define PORT 8080
  
// Main Code
int main()
{
    // Initialize Variables:
    int sock, valread;
    struct sockaddr_in cli_addr;
    struct sockaddr_in serv_addr;
    char msg[4096];
  
    // Create Messag:
    printf("\ninput your message:");
    scanf("%[^\n]s", msg);
  
    // Create Socket:
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("opening socket");
        exit(-1);
    }
    else
    printf("\nsocket created\n");
  
    // Assign IP, PORT:
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(PORT);
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
    // Connect to Server Socket:
    if ((connect(sock, (struct sockaddr*)&cli_addr,sizeof(cli_addr)))==-1) 
    {
        perror("on connect");
        exit(-1);
    }
    else
    printf("\nconnection established\n");
  
    // Send Message:
    int l = strlen(msg);

    send(sock, msg, sizeof(msg), 0);
    printf("\nmessage sent!\n");
  
    // Receive Message:
    valread = recv(sock, msg, sizeof(msg),0);
    printf("\nmessage received: %s\n", msg);
  
    // Close Socket:
    close(sock);
}