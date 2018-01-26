#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "async_network_server.h"
#include <memory>
#include <QUdpSocket>

class UDPSocket : public AsyncNetworkServer
{
public:
  UDPSocket();
  ~UDPSocket();
  bool Shut() override;
protected:
  bool SocketReceive(MessageReport &report) override;
  bool SocketSend(const MessageReport &report) override;
  bool InitializeSocket() override;
private:
  std::unique_ptr<QUdpSocket> socket_;
  QHostAddress address_;
  unsigned int port_;
};

#endif // UDP_SOCKET_H
