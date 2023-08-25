#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <tcp_connection.h>
#include <string.h>
#include <iostream>

using namespace std;

TcpConnection::TcpConnection(Epoll* epoll, int sockfd) 
    : epoll_(epoll),
      sockfd_(sockfd) {
  channel_ = new Channel(epoll, sockfd);
  channel_->SetHandler(this);
  channel_->EnableReading();
  channel_->Update();
}

TcpConnection::~TcpConnection() {

}


void TcpConnection::OnIn(int sockfd) {
  int readlength;
  char line[MAX_LINE];

  if (sockfd < 0) {
    cerr << "error: EPOLLIN sockfd < 0" << endl;
    return;
  }

  memset(line, 0, MAX_LINE);

  if ((readlength = read(sockfd, line, MAX_LINE)) < 0) {
    if(errno == ECONNRESET) {
      cout << "ECONNREST, close socket fd: " << sockfd << endl;
      close(sockfd);
    }
  } else if (readlength == 0) {
    cout << "read nothing, close socket fd: " << sockfd << endl;
  } else {
    string buf(line, MAX_LINE);
    user_->OnMessage(this, buf);
  }

}

void TcpConnection::Send(const string &msg) {

}

void TcpConnection::SetUser(ServerUser* user) {
  user_ = user;
}






