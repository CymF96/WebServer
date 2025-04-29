In the context of sockets, file descriptors, or I/O operation, non- blocking mode means that system call (e,g, read(), write(), accept()) return immediately if they cannot perform the requested operation, instead of waiting (or "blocking") until the operation can proceed.

In blocking mode, system call like read() or accept() will pause the program until the operation can be completed.
read() will block until data is available to read.
accept() will block until a client connects to the server.

In non-blocking mode, system calls retun immediately if the operation cannot be completed. Instead of blocking, the system call returns an error (e.g., -1) and sets errno to EAGAIN or EWOULDBLOCK, indicating that the operation would block if it were in blocking mode.

Why NBM
NOn=blocking mode is useful in scenarios where you need to handle multiple tasks or connections simulaneously without being stuck waiting for one operation to complete. For exmpale:

Event-Driven Servers" Servers using epoll, select, or poll to handle multple client connections.

Block:
int client_fd = accept(server_fd, NULL, NULL);

// If no client is connecting, the program will block (pause) here until a client connects.

Non-blocking mode:
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <errno.h>

void setNonBlockingMode(int socket_fd) {
    int flags = fcntl(socket_fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return;
    }
    if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        return;
    }
    std::cout << "Socket set to non-blocking mode" << std::endl;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return -1;
    }

    // Set the socket to non-blocking mode
    setNonBlockingMode(server_fd);

    // Bind the socket to a port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind");
        close(server_fd);
        return -1;
    }

    // Start listening for connections
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        return -1;
    }

    std::cout << "Server is running on port 8080..." << std::endl;

    // Accept connections in a loop
    while (true) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No client is connecting right now, continue the loop
                std::cout << "No connection yet, waiting..." << std::endl;
                usleep(100000); // Sleep for 100ms to avoid busy-waiting
                continue;
            } else {
                // An actual error occurred
                perror("accept");
                break;
            }
        }

        // Handle the new client connection
        std::cout << "New client connected!" << std::endl;

        // Close the client socket after handling (for simplicity)
        close(client_fd);
    }

    close(server_fd);
    return 0;
}