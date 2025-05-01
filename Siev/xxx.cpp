#include <iostream>
#include <cstring> // For memset, memcpy
#include <netdb.h> // For getaddrinfo, freeaddrinfo
#include <sys/socket.h> // For sockaddr_storage, socket functions
#include <netinet/in.h> // For sockaddr_in, sockaddr_in6, htons, ntohs
#include <arpa/inet.h> // For ntohs, htonl

void printAddress(const sockaddr_storage* storage)
{
    if (storage->ss_family == AF_INET)
    {
        //IPv4
        const sockaddr_in* ipv4 = (const sockaddr_in*)storage;
        const unsigned char* bytes = (const unsigned char*)&(ipv4->sin_addr.s_addr);
        std::cout << "IPv4 Address: "
                    << (int)bytes[0] << "." << (int)bytes[1] << "."
                    << (int)bytes[2] << "." << (int)bytes[3]
                    << ", Port: " >> 

    }
    else if (storage->ss_family == AF_INET6)
    {






    }


}


The expression ntohs(ipv4->sin_port) is used to convert the port from network
byte order to host byte order. Here's a detailed explanation.

What is ntohs?
ntohs stand network to host short. 
It is a function provided in <arpa/inet.h> that converts a 16-bit integer (a "short")
from netwrok byte order (big-endia to )

htons, htonl, ntohs, ntohl

notoh 16bit (2bytes)

#include <iostream>
#include <cstring> // For memset
#include <netdb.h> // For getaddrinfo, freeaddrinfo
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For ntohs

void printAddress(const sockaddr_storage* storage) {
    if (storage->ss_family == AF_INET) {
        // IPv4
        const sockaddr_in* ipv4 = (const sockaddr_in*)storage;
        const unsigned char* bytes = (const unsigned char*)&(ipv4->sin_addr.s_addr);
        std::cout << "IPv4 Address: "
                  << (int)bytes[0] << "." << (int)bytes[1] << "."
                  << (int)bytes[2] << "." << (int)bytes[3]
                  << ", Port: " << ntohs(ipv4->sin_port) << std::endl;
    } else if (storage->ss_family == AF_INET6) {
        // IPv6
        const sockaddr_in6* ipv6 = (const sockaddr_in6*)storage;
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

    // Resolve the hostname or IP address
    int status = getaddrinfo("example.com", "80", &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Iterate through the results and copy to sockaddr_storage
    for (struct addrinfo* p = res; p != NULL; p = p->ai_next) {
        sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage)); // Clear the memory

        // Copy the address into sockaddr_storage
        memcpy(&storage, p->ai_addr, p->ai_addrlen);

        // Print the address
        printAddress(&storage);
    }

    freeaddrinfo(res); // Free the linked list
    return 0;
}

int status = getaddrinfo("example.com", "http", NULL, &res);
if (status != 0) {
    printf("getaddrinfo error: %s\n", gai_strerror(status));
}
