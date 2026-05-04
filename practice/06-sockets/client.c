#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket creation");
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    server_address.sin_port = htons(8080);

    if (connect(socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)) == -1) {
        perror("connect");
        return 1;
    }

    char buff;
    while (read(socket_fd, &buff, 1) != 0) {
        printf("%c", buff);
    }
    
    
    return 0;
}
