#include <channel.h>
#include <epoll.h>
using namespace std;

Channel::Channel(Epoll* epoll, int sockfd)
    : epoll_(epoll),
      sockfd_(sockfd) {

}

int Channel::GetSockfd() {
  return sockfd_;
}

void Channel::SetRevent(int event) {
  revent_ = event;
}

void Channel::SetHandler(ChannelHandler* handler) {
  handler_ = handler;
}

int Channel::GetEvent() {
  return event_;
}

void Channel::EnableReading() {
  event_ |= EPOLLIN;
}

void Channel::Update() {
  epoll_->UpdateChannel(this);
}

void Channel::HandleRevent() {
  if (revent_ & EPOLLIN) {

  }
}