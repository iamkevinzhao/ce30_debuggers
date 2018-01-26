#include "tcp_socket.h"
#include <QHostAddress>
#include <QDebug>
#include <QThread>

using namespace std;

TCPSocket::TCPSocket() : socket_receive_(nullptr)
{

}

bool TCPSocket::Initialize() {
  AsyncNetworkServer::Initialize();
  return true;
}

bool TCPSocket::InitializeSocket() {
  server_.reset(new QTcpServer);
  server_->listen(QHostAddress::Any, 2368);
  socket_send_.reset(new QTcpSocket);
  socket_send_->connectToHost(QHostAddress("127.0.0.1"), 2368);
  while (!server_->hasPendingConnections()) {
    qDebug() << "waiting";
    QThread::sleep(1);
  }
  return true;
}

bool TCPSocket::SocketSend(const MessageReport &report) {
  socket_send_->write(report.message.data(), report.message.size());
  return true;
}

bool TCPSocket::SocketReceive(MessageReport &report) {
  if (!socket_receive_) {
    if (server_->hasPendingConnections()) {
      socket_receive_ = server_->nextPendingConnection();
    } else {
      return false;
    }
  }

  if (!socket_receive_->bytesAvailable()) {
    return false;
  }

  report.stamp = QTime::currentTime();
  report.message.append(socket_receive_->bytesAvailable(), 0);
  socket_receive_->read(report.message.data(), socket_receive_->bytesAvailable());
  return true;
}
