#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "abstract_socket.h"
#include <memory>
#include <QTcpSocket>
#include <QTcpServer>

class TCPSocket : public AbstractSocket
{
public:
  TCPSocket();
  bool Initialize() override;
  MessageReport Send(const QString& message) override;
  std::vector<MessageReport> AsyncReceive() override;
private:
  std::unique_ptr<QTcpSocket> socket_;
  std::unique_ptr<QTcpSocket> socket_receive_;
  std::unique_ptr<QTcpServer> server_;
};

#endif // TCP_SOCKET_H
