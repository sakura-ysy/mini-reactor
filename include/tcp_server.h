#pragma once
#include <sys/epoll.h>
#include <acceptor.h>
#include <tcp_connection.h>
#include <epoll.h>
#include <server_user.h>
#include <map>

using namespace std;

class TcpServer {
public:
  TcpServer(Epoll* epoll);
  ~TcpServer();

  void Start();

  void SetUser(ServerUser* user);

private:
  map<int, TcpConnection> connections_;
  Acceptor* acceptor_;
  Epoll* epoll_;
  ServerUser* user_;
};