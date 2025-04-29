#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <vector>

#define MAX_EVENTS 10
#define PORT 8080

// Helper function to set a socket to non-blocking mode
void setNonBlocking(int socket_fd) {
    int flags = fcntl(socket_fd, F_GETFL, 0);
    fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
}




int main() {
    // Step 1: Create a listening socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    // Step 2: Create an epoll instance
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Epoll creation failed");
        close(server_fd);
        return 1;
    }

    // Step 3: Add the listening socket to the epoll instance
    epoll_event event{};
    event.events = EPOLLIN; // Monitor for incoming connections
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        perror("Epoll_ctl failed");
        close(server_fd);
        close(epoll_fd);
        return 1;
    }

    // Step 4: Event loop
    epoll_event events[MAX_EVENTS];
    while (true) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("Epoll_wait failed");
            break;
        }

        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == server_fd) {
                // Step 5: Accept new connections
                int client_fd = accept(server_fd, nullptr, nullptr);
                if (client_fd == -1) {
                    perror("Accept failed");
                    continue;
                }

                std::cout << "New client connected: " << client_fd << std::endl;

                // Set the client socket to non-blocking mode
                setNonBlocking(client_fd);

                // Add the client socket to the epoll instance
                epoll_event client_event{};
                client_event.events = EPOLLIN | EPOLLET; // Monitor for incoming data (edge-triggered)
                client_event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
                    perror("Epoll_ctl failed for client");
                    close(client_fd);
                }
            } else {
                // Step 6: Handle client data
                char buffer[1024];
                int client_fd = events[i].data.fd;
                int bytes_read = read(client_fd, buffer, sizeof(buffer));
                if (bytes_read <= 0) {
                    // Client disconnected or error
                    std::cout << "Client disconnected: " << client_fd << std::endl;
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
                } else {
                    // Echo the data back to the client
                    std::cout << "Received from client " << client_fd << ": " << std::string(buffer, bytes_read) << std::endl;
                    write(client_fd, buffer, bytes_read);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}

