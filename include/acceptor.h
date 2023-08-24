#pragma once
#include <channel.h>
#include <epoll.h>
#include <macro.h>
#include <channel_handler.h>

using namespace std;

class Acceptor : ChannelHandler{
public:
  Acceptor(Epoll* epoll);
  ~Acceptor();

  void Start();

  void onIn(int sockfd) override;

private:
  void BindAndListen();

  void newConnection(int sockfd);

  int listenfd_;
  Channel* channel_;
  Epoll* epoll_;
};
