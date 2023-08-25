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
  acceptor_->SetUser(user_);
  epoll_->Loop();
}

void TcpServer::SetUser(ServerUser* user) {
  user_ = user;
}