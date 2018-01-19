#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "abstract_socket.h"

class UDPSocket : public AbstractSocket
{
public:
  UDPSocket();
  void Test() override;
};

#endif // UDP_SOCKET_H
