#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "async_network_server.h"
#include <memory>
#include <QTcpSocket>

class TCPSocket : public AsyncNetworkServer
{
  Q_OBJECT
public:
  TCPSocket();
  ~TCPSocket();
  bool Initialize() override;
  MessageReport AsyncSend(const QString& message) override;
  std::vector<MessageReport> AsyncReceive() override;
  bool Shut() override;
protected:
  bool SocketReceive(MessageReport &report) override;
  bool SocketSend(const MessageReport &report) override;
  bool InitializeSocket() override;
public slots:
  void ReadyRead();
private:
  QTcpSocket* socket_;
  std::vector<MessageReport> report_cache_;
};

#endif // TCP_SOCKET_H
