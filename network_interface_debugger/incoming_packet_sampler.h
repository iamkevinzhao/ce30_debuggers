#ifndef INCOMING_PACKET_SAMPLER_H
#define INCOMING_PACKET_SAMPLER_H

#include <memory>
#include "async_network_server.h"
#include <QElapsedTimer>

class IncomingPacketSampler
{
public:
  IncomingPacketSampler();
  void SetNetworkServer(std::shared_ptr<AsyncNetworkServer> server);
  bool InspectCommand(const QString& command);
  float Frequency();
private:
  bool InMessageEnqueueJudge(const MessageReport& report);
  std::shared_ptr<AsyncNetworkServer> server_;
  QString start_measurement_command_;
  QElapsedTimer timer_;
  float interval_; // in milliseconds
};

#endif // INCOMING_PACKET_SAMPLER_H
