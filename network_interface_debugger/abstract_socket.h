#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#include <QString>
#include <QTime>
#include <vector>
#include <QHostAddress>
#include <QObject>

struct MessageReport {
  QTime stamp;
  QByteArray message;
  bool success;
};

class AbstractSocket : public QObject
{
  Q_OBJECT
public:
  AbstractSocket();
  virtual ~AbstractSocket();
  virtual bool Initialize() = 0;
  void SetIP(const QString& ip);
  void SetPort(const quint16& port);
  virtual MessageReport AsyncSend(const QString& message) = 0;
  virtual std::vector<MessageReport> AsyncReceive() = 0;
  virtual bool Shut() = 0;
  QString GetIP();
  quint16 GetPort();
private:
  QString ip_;
  quint16 port_;
};

#endif // ABSTRACT_SOCKET_H
