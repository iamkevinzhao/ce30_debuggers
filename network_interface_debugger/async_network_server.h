#ifndef ASYNC_NETWORK_SERVER_H
#define ASYNC_NETWORK_SERVER_H

#include "abstract_socket.h"
#include <memory>
#include <thread>
#include <mutex>
#include <queue>

class AsyncNetworkServer : public AbstractSocket
{
public:
  AsyncNetworkServer();
  virtual ~AsyncNetworkServer();
  bool Initialize() override;
  MessageReport AsyncSend(const QString& message) override;
  std::vector<MessageReport> AsyncReceive() override;
  bool Shut() override;
  bool SetInMessageEnqueueJudgeToDefault();
  bool SetInMessageEnqueueJudge(
      std::function<bool(const MessageReport&)> function);
protected:
  virtual bool InitializeSocket() = 0;
  virtual bool SocketSend(const MessageReport& report) = 0;
  virtual bool SocketReceive(MessageReport& report) = 0;
private:
  void BackgroudThread();

  int report_queue_in_max_;

  std::unique_ptr<std::thread> thread_;
  bool exit_signal_;

  std::mutex report_queue_out_mutex_;
  std::queue<MessageReport> report_queue_out_;

  std::mutex report_queue_in_mutex_;
  std::queue<MessageReport> report_queue_in_;

  std::function<bool(const MessageReport&)> in_message_enqueue_judge_;
};

#endif // ASYNC_NETWORK_SERVER_H
