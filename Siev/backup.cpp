#include <iostream>
#include <cstring> // memset
#include <netdb.h> // getaddrinfo, freeaddrinfo
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_pton

void printAddress(const struct addrinfo* res) {
    sockaddr_storage storage;
    memset(&storage, 0, sizeof(storage)); // Clear the memory

    // Copy the address from addrinfo to sockaddr_storage
    memcpy(&storage, res->ai_addr, res->ai_addrlen);

    // Check the address family
    if (storage.ss_family == AF_INET) {
        // IPv4
        sockaddr_in* ipv4 = (sockaddr_in*)&storage;
        unsigned char* bytes = (unsigned char*)&(ipv4->sin_addr.s_addr);
        std::cout << "IPv4 Address: "
                  << (int)bytes[0] << "." << (int)bytes[1] << "."
                  << (int)bytes[2] << "." << (int)bytes[3]
                  << ", Port: " << ntohs(ipv4->sin_port) << std::endl;
    } else if (storage.ss_family == AF_INET6) {
        // IPv6
        sockaddr_in6* ipv6 = (sockaddr_in6*)&storage;
        const unsigned char* bytes = ipv6->sin6_addr.s6_addr;
        std::cout << "IPv6 Address: ";
        for (int i = 0; i < 16; i++) {
            if (i > 0 && i % 2 == 0) std::cout << ":";
            printf("%02x", bytes[i]);
        }
        std::cout << ", Port: " << ntohs(ipv6->sin6_port) << std::endl;
    } else {
        std::cerr << "Unknown address family!" << std::endl;
    }
}

int main() {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Support both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    int status = getaddrinfo("example.com", "80", &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Iterate through the results and print the addresses
    for (struct addrinfo* p = res; p != NULL; p = p->ai_next) {
        printAddress(p);
    }

    freeaddrinfo(res); // Free the linked list
    return 0;
}