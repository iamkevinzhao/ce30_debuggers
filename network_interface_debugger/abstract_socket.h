#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#include <QString>
#include <QTime>
#include <vector>

struct MessageReport {
  QTime stamp;
  QByteArray message;
  bool success;
};

class AbstractSocket
{
public:
  AbstractSocket();
  virtual ~AbstractSocket();
  virtual bool Initialize() = 0;
  virtual MessageReport AsyncSend(const QString& message) = 0;
  virtual std::vector<MessageReport> AsyncReceive() = 0;
  virtual bool Shut() = 0;
};

#endif // ABSTRACT_SOCKET_H
