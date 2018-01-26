#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "abstract_socket.h"
#include <memory>
#include <thread>
#include <mutex>
#include <QUdpSocket>
#include <condition_variable>

class UDPSocket : public AbstractSocket
{
public:
  UDPSocket();
  ~UDPSocket();
  bool Initialize() override;
  MessageReport AsyncSend(const QString& message) override;
  std::vector<MessageReport> AsyncReceive() override;
private:
  void InterfaceThread();
  std::unique_ptr<std::thread> thread_;

  std::mutex send_datagram_mutex_;
  MessageReport send_datagram_;

  bool exit_signal_;
  std::unique_ptr<QUdpSocket> socket_;
  QHostAddress address_;
  unsigned int port_;

  std::mutex receive_datagrams_mutex_;
  std::vector<MessageReport> receive_datagrams_;
};

#endif // UDP_SOCKET_H
