#include <iostream>
#include <string>

int main()
{
    
    std::string hi = "Hello, World!";

    int len = hi.length();
    size_t size = hi.length();
    std::cout << len << "\n";
    std::cout << size << "\n";
    std::cout << sizeof(int) << "\n"; 
    std::cout << sizeof(size_t) << "\n";

}









// char *msg = "Beej was here!";
// int len, bytes_sent;
// .
// .
// .
// len = strlen(msg);
// bytes_sent = send(sockfd, msg, len, 0);