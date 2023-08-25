#pragma once
#include <server_user.h>
#include <tcp_server.h>

using namespace std;

class EchoServer : public ServerUser {
public: 
  EchoServer(Epoll* epoll);
  ~EchoServer();

  void Start();

  void OnConnection(TcpConnection* tcp) override;

  void OnMessage(TcpConnection* tcp, const string &msg) override;

private:
  Epoll* epoll_;
  TcpServer* server_;
};