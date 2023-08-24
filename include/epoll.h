#pragma once

#include <sys/epoll.h>
#include <vector>
#include <channel.h>
#include <macro.h>

using namespace std;

class Epoll {
public:
  Epoll();
  ~Epoll();

  void PollEvents(vector<Channel*> &channels);
  
  void UpdateChannel(Channel* channel);

  void Loop();
  
private:

  int epollfd_;
  bool quit_;
};