#include <iostream> //std::cout, std::cerr
#include <cerrno> //errno
#include <cstdio> //perro
#include <unistd.h> //close, read, write, 
#include <netdb.h> //getaddrinfo, free
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void ft_memset(void* ptr, int value, size_t size)
{
    unsigned char *p = (unsigned char*)ptr;
    size_t i = 0;

    for (size_t i = 0; i < size; i++)
        p[i] = 0;
}

void ft_memcpy(void* dest, const void*src, size_t size)
{
    const unsigned char* s = (const unsigned char *)src;
    unsigned char* d = (unsigned char *)dest;
    for (size_t i = 0; i < size; i++)
        d[i] = s[i];
}

void ft_memset(void* ptr, int value, size_t size)
{
    unsigned char *p = (unsigned char*)ptr;
    size_t i = 0;

    // Set memory in chunks of 4 bytes (if size is large enough)
    unsigned int chunk = (unsigned char)value | ((unsigned char)value << 8) |
                         ((unsigned char)value << 16) | ((unsigned char)value << 24);
    for (; i + 4 <= size; i += 4)
        *((unsigned int*)(p + i)) = chunk;

    // Set remaining bytes
    for (; i < size; i++)
        p[i] = (unsigned char)value;
}

void ft_memcpy(void* dest, const void* src, size_t size)
{
    const unsigned char* s = (const unsigned char*)src;
    unsigned char* d = (unsigned char*)dest;
    size_t i = 0;

    // Copy memory in chunks of 4 bytes (if size is large enough)
    for (; i + 4 <= size; i += 4)
        *((unsigned int*)(d + i)) = *((const unsigned int*)(s + i));

    // Copy remaining bytes
    for (; i < size; i++)
        d[i] = s[i];
}



