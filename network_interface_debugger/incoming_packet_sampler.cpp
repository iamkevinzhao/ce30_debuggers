#include "incoming_packet_sampler.h"
#include <QDebug>

using namespace std;

IncomingPacketSampler::IncomingPacketSampler() : interval_(5000)
{
  start_measurement_command_ = "getDistanceAndAmplitudeSorted";
  start_measurement_command_.append(
      QString(50 - start_measurement_command_.size(), 0));
  timer_.start();
}

void IncomingPacketSampler::SetNetworkServer(
    std::shared_ptr<AsyncNetworkServer> server) {
  server_ = server;
}

bool IncomingPacketSampler::InspectCommand(const QString &command) {
  if (command == start_measurement_command_) {
    server_->SetInMessageEnqueueJudge(
        bind(&IncomingPacketSampler::InMessageEnqueueJudge, this, std::placeholders::_1));
    return true;
  } else {
    server_->SetInMessageEnqueueJudgeToDefault();
    return false;
  }
}

float IncomingPacketSampler::Frequency() {
  return 1000.0f / interval_;
}

bool IncomingPacketSampler::InMessageEnqueueJudge(const MessageReport &report) {
  if (timer_.elapsed() > interval_) {
    timer_.start();
    return true;
  } else {
    return false;
  }
}
