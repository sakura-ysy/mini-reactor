#pragma once
#include<tcp_connection.h>
#include <string>

using namespace std;

class ServerUser {
public:
  void virtual OnConnection(TcpConnection* tcp) = 0;

  void virtual OnMessage(TcpConnection* tcp, const string &data) = 0;
};