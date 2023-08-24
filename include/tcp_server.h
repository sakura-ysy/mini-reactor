#pragma once
#include <sys/epoll.h>
#include <acceptor.h>
#include <tcp_connection.h>
#include <epoll.h>
#include <map>

using namespace std;

class TcpServer {
public:
  TcpServer(Epoll* epoll);
  ~TcpServer();

  void Start();

private:
  map<int, TcpConnection> connections_;
  Acceptor* acceptor_;
  Epoll* epoll_;
};