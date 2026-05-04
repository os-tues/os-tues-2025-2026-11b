#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket creation");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    if (bind(socket_fd, (struct sockaddr*) &address, sizeof(address)) == -1) {
        perror("bind");
        return 1;
    }

    if (listen(socket_fd, 5) == -1) {
        perror("listen");
        return 1;
    }


    // struct sockaddr_in incomming_address;
    // accept(socket_fd, (struct sockaddr*) &incomming_address, sizeof(incomming_address));

    int client_socket = accept(socket_fd, NULL, NULL);
    if (client_socket == -1) {
        perror("client failed to connect");
    }
    
    write(client_socket, "Hello there!", 12);
    close(client_socket);

    close(socket_fd);
    return 0;
}

