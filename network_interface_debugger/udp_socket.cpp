#include "udp_socket.h"
#include <QDebug>

using namespace std;

UDPSocket::UDPSocket()
  : address_("192.168.1.80"), port_(2368)
{

}

UDPSocket::~UDPSocket() {
}

bool UDPSocket::Shut() {
  AsyncNetworkServer::Shut();
  socket_->close();
  return true;
}

bool UDPSocket::SocketSend(const MessageReport &report) {
  if (report.message.size()) {
    socket_->writeDatagram(report.message, address_, port_);
    return true;
  }
  return false;
}

bool UDPSocket::SocketReceive(MessageReport &report) {
  if (!socket_->hasPendingDatagrams()) {
    return false;
  }
  report.message.resize(socket_->pendingDatagramSize());
  QHostAddress address;
  quint16 port;
  socket_->readDatagram(
      report.message.data(), report.message.size(), &address, &port);
  report.stamp = QTime::currentTime();
//  if ((address == address_) && (port == port_)) {
//    return true;
//  } else {
//    return false;
//  }
  return true;
}

bool UDPSocket::InitializeSocket() {
  socket_.reset(new QUdpSocket);
  socket_->bind(QHostAddress::Any, port_);
  return true;
}
