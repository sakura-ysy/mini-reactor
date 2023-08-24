#include <tcp_connection.h>

using namespace std;

TcpConnection::TcpConnection(Epoll* epoll, int sockfd) 
    : epoll_(epoll),
      sockfd_(sockfd) {

}

