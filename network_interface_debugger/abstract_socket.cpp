#include "abstract_socket.h"

AbstractSocket::AbstractSocket() : ip_("192.168.1.80"), port_(2368)
{

}

AbstractSocket::~AbstractSocket() {}

void AbstractSocket::SetIP(const QString &ip) {
  ip_ = ip;
}

void AbstractSocket::SetPort(const quint16 &port) {
  port_ = port;
}

QString AbstractSocket::GetIP() {
  return ip_;
}

quint16 AbstractSocket::GetPort() {
  return port_;
}
