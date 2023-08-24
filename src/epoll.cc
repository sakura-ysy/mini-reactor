#include <epoll.h>
#include <iostream>
#include <unistd.h>
using namespace std;

Epoll::Epoll() {
  epollfd_ = epoll_create(1);
  if (epollfd_ < 0) {
    cerr << "epoll_create error, errno is : " << epollfd_ << endl;
  }
}

Epoll::~Epoll() {
  //close(epollfd_);
}

void Epoll::PollEvents(vector<Channel*> &channels){
  struct epoll_event* events;
  int fds = epoll_wait(epollfd_, events, MAX_EVENTS, -1);
  
  if (fds == -1) {
    cerr << "epoll_wait error." << endl;
    return;
  }

  for (int i = 0; i < fds; i++) {
    Channel* channel = static_cast<Channel*>(events[i].data.ptr);
    channel->SetRevent(events[i].events);
    channels.push_back(channel);
  }
}

void Epoll::UpdateChannel(Channel* channel) {
  struct epoll_event* ev;
  ev->data.ptr = channel;
  ev->events = channel->GetEvent();
  int sockfd = channel->GetSockfd();
  epoll_ctl(epollfd_, EPOLL_CTL_ADD, sockfd, ev);
}

void Epoll::Loop() {
  while (!quit_) {
    vector<Channel*> channels;
    PollEvents(channels);
    for (auto channel : channels) {
      channel->HandleRevent();
    }
  }
}

