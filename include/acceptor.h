#pragma once
#include <channel.h>
#include <epoll.h>
#include <macro.h>
#include <channel_handler.h>
#include <unordered_map>
#include <server_user.h>

using namespace std;

class Acceptor : ChannelHandler{
public:
  Acceptor(Epoll* epoll);
  ~Acceptor();

  void Start();

  void OnIn(int sockfd) override;

  void SetUser(ServerUser* user);

private:
  void BindAndListen();

  void NewConnection(int sockfd);

  int listenfd_;
  Channel* channel_;
  Epoll* epoll_;
  unordered_map<int, TcpConnection*> connections_;
  ServerUser* user_;
};
