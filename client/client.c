#include<stdio.h>
#include<string.h>   
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char message[2000] , server_reply[2000];
    int port;

    if (argc != 3){
        perror("參數錯誤");
    }

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    sscanf(argv[2],"%d",&port);

    server.sin_port = htons( port );
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
    puts("Connected\n");
    while (1)
    {
        printf("Input : ");
        scanf("%s", &message);
        if (send(socket_desc, message, strlen(message), 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        puts("Data Send：");
        puts(message);
        if (recv(socket_desc, server_reply, 2000, 0) < 0)
        {
            puts("recv failed");
        }
        puts("Reply received:");
        puts(server_reply);
    }

    return 0;
}
