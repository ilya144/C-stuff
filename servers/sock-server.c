#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


char* response = \
"HTTP/1.1 200 OK\n\
Server: pupsik777\n\
Content-Type: text/html; charset=utf-8\n\
Connection: close\n\
\n\
<html>\n\
    <body>Hello there</body>\n\
</html>\n";

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1000];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        bytes_read = recv(sock, buf, 1000, 0);
        printf("Bytes: %d", bytes_read);


        send(sock, response, strlen(response), 0);
        
        close(sock);
    }
    
    return 0;
}

