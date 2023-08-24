// handler基类
// Accpetor和TpcConnection分别继承
class ChannelHandler {
public:
  void virtual onIn(int sockfd) = 0;
};