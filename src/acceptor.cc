#include <acceptor.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <iostream>
#include <tcp_connection.h>

using namespace std;

Acceptor::Acceptor(Epoll* epoll) 
    : epoll_(epoll),
      channel_(nullptr) {

}

Acceptor::~Acceptor() {

}

void Acceptor::Start() {
  BindAndListen();
  channel_ = new Channel(epoll_, listenfd_);
  channel_->SetHandler(this);
  channel_->EnableReading();
  channel_->Update();
}

void Acceptor::SetUser(ServerUser* user) {
  user_ = user;
}

void Acceptor::BindAndListen() {
  int on = 1;
  listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  fcntl(listenfd_, F_SETFL, O_NONBLOCK); // no-block io
  setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(11111);
  
  if (bind(listenfd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    cerr << "bind error, errno is : " << errno << endl;
  }

  if (listen(listenfd_, MAX_LISTENFD)) {
    cerr << "listen error, errno is :" << errno << endl;
  }
}

void Acceptor::OnIn(int sockfd) {
  int connfd;
  struct sockaddr_in cliaddr;
  socklen_t clilen = sizeof(sockaddr_in);
  connfd = accept(listenfd_, (sockaddr*)&cliaddr, (socklen_t*)&clilen);
  if (connfd > 0) {
    cout << "new connection from "
        << "[" << inet_ntoa(cliaddr.sin_addr) 
        << ":" << ntohs(cliaddr.sin_port) << "]"
        << " new socket fd:" << connfd
        << endl;
  } else {
    cout << "accept error, connfd:" << connfd
        << " errno:" << errno << endl;
  }

  fcntl(connfd, F_SETFL, O_NONBLOCK);  // no-block io

  NewConnection(connfd);
}

void Acceptor::NewConnection(int sockfd) {
  TcpConnection* tcp = new TcpConnection(epoll_, sockfd);
  tcp->SetUser(user_);
  connections_[sockfd] = tcp;
}

