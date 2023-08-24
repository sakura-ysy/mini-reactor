#include <tcp_server.h>
using namespace std;

TcpServer::TcpServer(Epoll* epoll)
    : epoll_(epoll), 
      acceptor_(nullptr) {

}

TcpServer::~TcpServer() {

}     


void TcpServer::Start() {
  acceptor_ = new Acceptor(epoll_);
  acceptor_->Start();
  epoll_->Loop();
}