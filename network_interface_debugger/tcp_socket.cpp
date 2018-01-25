#include "tcp_socket.h"
#include <QHostAddress>

using namespace std;

TCPSocket::TCPSocket()
{

}

bool TCPSocket::Initialize() {
  socket_.reset(new QTcpSocket);
  socket_->connectToHost(QHostAddress("192.168.1.80"), 2368);
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
  vector<MessageReport> reports;
  return reports;
}
