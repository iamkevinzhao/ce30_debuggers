#include "tcp_socket.h"
#include <QHostAddress>
#include <QDebug>

using namespace std;

TCPSocket::TCPSocket()
{

}

bool TCPSocket::Initialize() {
  socket_.reset(new QTcpSocket);
  socket_->connectToHost(QHostAddress("127.0.0.1"), 2368);
  server_.reset(new QTcpServer);
  server_->listen(QHostAddress::Any, 2368);
  return true;
}

MessageReport TCPSocket::Send(const QString& message) {
  MessageReport report;
  report.message = message.toLocal8Bit();
  socket_->write(report.message.data(), message.size());
  report.stamp = QTime::currentTime();
  report.success = true;
  return report;
}

vector<MessageReport> TCPSocket::AsyncReceive() {
  if (!socket_receive_) {
    if (server_->hasPendingConnections()) {
      socket_receive_.reset(server_->nextPendingConnection());
    } else {
      return vector<MessageReport>();
    }
  }
  if (socket_receive_->bytesAvailable() <= 0) {
    return vector<MessageReport>();
  }
  MessageReport report;
  report.stamp = QTime::currentTime();
  report.message.append(socket_receive_->bytesAvailable(), 0);
  socket_receive_->read(report.message.data(), socket_receive_->bytesAvailable());
  vector<MessageReport> reports;
  reports.push_back(report);
  return reports;
}
