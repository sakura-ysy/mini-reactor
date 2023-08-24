#pragma once
#include <channel.h>
#include <epoll.h>
#include <channel_handler.h>

using namespace std;

class TcpConnection : ChannelHandler {
public:
  TcpConnection(Epoll* epoll, int sockfd);
  ~TcpConnection();

  void onIn(int sockfd) override;

private:
  int sockfd_;
  Channel* channel_;
  Epoll* epoll_;
};
