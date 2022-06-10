// Server Side Code
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
    int sock, client_sock, valread;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int addrsize = sizeof(cli_addr);
    char msg[4096]; 

    // Create Socket:
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("opening socket");
        exit(-1);
    }
    else
    printf("\nsocket created\n");
    bzero(&serv_addr, sizeof(serv_addr));

    // Assign IP, PORT:
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind Socket:
    if ((bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))==-1)
    {
        perror("on bind");
        exit(-1);
    }
    else
    printf("\nbind established\n");

    // Listen and Wait:
    if ((listen(sock,4))==-1)
    {
        perror("on listen");
        exit(-1);
    }
    else
    printf("\nlistening...\n");

    // Accept Client Socket:
    client_sock = accept(sock, (struct sockaddr*)&serv_addr, &addrsize);
    if (client_sock == - 1)
    {
        perror("on accept");
        exit(-1);
    }
    else
    printf("\nconnection made with client\n");

    // Receive Client Message:
    valread = recv(client_sock, msg, sizeof(msg), 0);

    printf("\nclient message: %s\n", msg);

    // Send Reversed Message:
    int i, j, temp;
    int l = strlen(msg);

    for (i = 0, j = l - 1; i < j; i++, j--)
    {
        temp = msg[i];
        msg[i] = msg[j];
        msg[j] = temp;
    }

    send(client_sock, msg, sizeof(msg), 0);

    printf("\nsent message to client\n");

    // Close Both Sockets:
    close(client_sock);
    close(sock);
}