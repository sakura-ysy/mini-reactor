// handler基类
// Accpetor和TpcConnection分别继承
class ChannelHandler {
public:
  void virtual OnIn(int sockfd) = 0;
};