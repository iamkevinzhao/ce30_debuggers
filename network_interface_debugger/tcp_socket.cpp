#include "tcp_socket.h"
#include <QHostAddress>
#include <QDebug>
#include <QThread>

using namespace std;

TCPSocket::TCPSocket()
{

}

TCPSocket::~TCPSocket() {
  if (socket_) {
    delete socket_;
  }
}

bool TCPSocket::Initialize() {
  socket_ = new QTcpSocket(this);

  connect(socket_, SIGNAL(readyRead()), this, SLOT(ReadyRead()));

  socket_->connectToHost(GetIP(), GetPort());
  return true;
}

MessageReport TCPSocket::AsyncSend(const QString &message) {
  MessageReport report;
  report.stamp = QTime::currentTime();
  report.message = message.toLocal8Bit();
  report.success = true;
  socket_->write(report.message);
  return report;
}

std::vector<MessageReport> TCPSocket::AsyncReceive() {
  auto result = std::move(report_cache_);
  report_cache_.clear();
  return std::move(result);
}

void TCPSocket::ReadyRead() {
  MessageReport report;
  report.stamp = QTime::currentTime();
  report.message = socket_->readAll();
  report.success = true;
  if (ShouldEnqueueMessage(report)) {
    report_cache_.emplace_back(std::move(report));
  }
}

bool TCPSocket::Shut() {
  return true;
}

bool TCPSocket::InitializeSocket() {
  return false;
}

bool TCPSocket::SocketSend(const MessageReport &report) {
  return false;
}

bool TCPSocket::SocketReceive(MessageReport &report) {
  return false;
}
