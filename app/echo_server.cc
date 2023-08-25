#include <echo_server.h>
#include <iostream>

EchoServer::EchoServer(Epoll* epoll)
    : epoll_(epoll) {
  server_ = new TcpServer(epoll);
  server_->SetUser(this);
}

EchoServer::~EchoServer() {

}

void EchoServer::Start() {
  server_->Start();
}

void EchoServer::OnConnection(TcpConnection* tcp) {
  cout << "EchoServer::OnConnetion" << endl;
}

void EchoServer::OnMessage(TcpConnection* tcp, const string &msg) {
  cout << "EchoServer::OnMessage" << endl;
  tcp->Send(msg);
} 




