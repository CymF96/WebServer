#include <iostream>
#include <cstring> // memset
#include <netdb.h> // getaddrinfo, freeaddrinfo
#include <sys/socket.h> // sockaddr_storage
#include <netinet/in.h> // sockaddr_in, sockaddr_in6
#include <arpa/inet.h> // inet_pton

void printAddress(const struct addrinfo* res)
{
    sockaddr_storage storage;
    memset(&storage, 0, sizeof(storage)); //clear the memory

    // copy the address from add // this is super important
    memcpy(&storage, res->ai_addr, res->ai_addrlen); //ai_addr is just struct sockaddr *ai_addr;

    if (storage.ss_family == AF_INET)
    {
        //IPv4
        sockaddr_in* ipv4 = (sockaddr_in*)&storage;
        




    }
    else if (storage.ss_family == AF)




}

// IPv6 address
// structure: s

// 2    0    0    1
// 0010 0000 0000 0001

// 0    d    b    8
// 0000 1101 1011 1000

getaddrinfo() works and how it determins address types:

DNS resoultion:
it performs DNS lookups for the hostname
converts hostnames (e.g. "www.example.com") to IP address
can handle both IPv4 and IPv6 address

Service Resoultion:
converts service names (e.g. http) to port numbers
can take direct port numbers as strings (e.g. "80")

Filtering based on Hints;
The hints parameter tells getaddrinfo()
what kind of addresses you want:
struct addrinfo hints;
memset(&hints, 0, sizeof(hints));

//example settings:
hints.ai_family = AF_UNSPEC;
hints.ai.socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;