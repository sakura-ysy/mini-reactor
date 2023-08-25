#pragma once
#include <channel.h>
#include <epoll.h>
#include <channel_handler.h>
#include <server_user.h>

using namespace std;

class TcpConnection : ChannelHandler {
public:
  TcpConnection(Epoll* epoll, int sockfd);
  ~TcpConnection();

  void OnIn(int sockfd) override;

  void Send(const string &msg);

  void SetUser(ServerUser* user);

private:
  int sockfd_;
  Channel* channel_;
  Epoll* epoll_;
  ServerUser* user_;
};
