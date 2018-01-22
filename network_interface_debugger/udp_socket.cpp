#include "udp_socket.h"
#include <QDebug>

using namespace std;

UDPSocket::UDPSocket()
  : exit_signal_(false), address_("192.168.1.80"), port_(2368)
{

}

UDPSocket::~UDPSocket() {
  exit_signal_ = true;
  if (thread_ && thread_->joinable()) {
    thread_->join();
  }
}

bool UDPSocket::Initialize() {
  thread_.reset(new thread(&UDPSocket::InterfaceThread, this));
  return true;
}

MessageReport UDPSocket::Send(const QString &message) {
  MessageReport report;
  report.message = message.toUtf8();
  report.stamp = QTime::currentTime();
  unique_lock<mutex> lock(send_datagram_mutex_);
  send_datagram_.message = message.toUtf8();
  lock.unlock();
  return report;
}

vector<MessageReport> UDPSocket::AsyncReceive() {
  receive_datagrams_mutex_.lock();
  auto reports = receive_datagrams_;
  receive_datagrams_.clear();
  receive_datagrams_mutex_.unlock();
  return reports;
}

void UDPSocket::InterfaceThread() {
  socket_.reset(new QUdpSocket);
  socket_->bind(QHostAddress::Any, port_);
  while (true) {
    if (exit_signal_) {
      return;
    }
    send_datagram_mutex_.lock();
    if (send_datagram_.message.size()) {
      send_datagram_.stamp = QTime::currentTime();
      socket_->writeDatagram(send_datagram_.message, address_, port_);
      send_datagram_.message.clear();
    }
    send_datagram_mutex_.unlock();

    receive_datagrams_mutex_.lock();
    while (socket_->hasPendingDatagrams()) {
      if (receive_datagrams_.size() > 100000) {
        receive_datagrams_.clear();
      }
      MessageReport report;
      report.message.resize(socket_->pendingDatagramSize());
      QHostAddress address;
      quint16 port;
      socket_->readDatagram(
            report.message.data(), report.message.size(), &address, &port);
      report.stamp = QTime::currentTime();
      if (address == address_ || port == port_) {
        receive_datagrams_.push_back(report);
      }
    }
    receive_datagrams_mutex_.unlock();
  }
}
