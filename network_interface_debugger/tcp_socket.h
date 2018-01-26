#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "async_network_server.h"
#include <memory>
#include <QTcpSocket>
#include <QTcpServer>

class TCPSocket : public AsyncNetworkServer
{
public:
  TCPSocket();
  bool Initialize() override;
protected:
  bool SocketReceive(MessageReport &report) override;
  bool SocketSend(const MessageReport &report) override;
  bool InitializeSocket() override;
private:
  std::unique_ptr<QTcpSocket> socket_send_;
  QTcpSocket* socket_receive_;
  std::unique_ptr<QTcpServer> server_;
};

#endif // TCP_SOCKET_H
