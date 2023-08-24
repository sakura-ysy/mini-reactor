#pragma once
#include <epoll.h>
#include <channel_handler.h>

using namespace std;

// 一个 socket 对应一个 Channel
// 每个 Channel 自始至终只负责一个 socket 的 epoll IO事件分发
class Channel {
public:
  Channel(Epoll* epoll, int sockfd);
  ~Channel();
  
  int GetSockfd();

  void SetRevent(int event);

  void SetHandler(ChannelHandler* handler);

  int GetEvent();

  void EnableReading();

  void Update();

  void HandleRevent();

private:

  Epoll* epoll_;
  int sockfd_;
  int event_;  // 主动产生的事件，交给epoll更新
  int revent_; // 从epoll收到的事件，交给handle处理
  ChannelHandler* handler_;
};