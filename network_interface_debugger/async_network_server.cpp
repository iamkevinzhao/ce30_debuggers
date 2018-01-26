#include "async_network_server.h"
#include <QDebug>
#include <QThread>

using namespace std;

AsyncNetworkServer::AsyncNetworkServer()
  : exit_signal_(false),
    report_queue_in_max_(1000)
{

}

AsyncNetworkServer::~AsyncNetworkServer() {
  exit_signal_ = true;
  if (thread_) {
    if (thread_->joinable()) {
      thread_->join();
    }
  }
}

bool AsyncNetworkServer::Initialize() {
  if (!thread_) {
    thread_.reset(new thread(&AsyncNetworkServer::BackgroudThread, this));
  } else {
    return false;
  }
  return true;
}

MessageReport AsyncNetworkServer::AsyncSend(const QString &message) {
  MessageReport report;
  report.message = message.toLocal8Bit();
  report.stamp = QTime::currentTime();
  unique_lock<mutex> lock(report_queue_out_mutex_);
  if (report_queue_out_.size() <= report_queue_in_max_) {
    report_queue_out_.push(report);
  }
  lock.unlock();
  return report;
}

vector<MessageReport> AsyncNetworkServer::AsyncReceive() {
  report_queue_in_mutex_.lock();
  // auto reports = std::move(report_queue_in_);
  auto reports = std::move(report_queue_in_);
  report_queue_in_ = {};
  report_queue_in_mutex_.unlock();
  vector<MessageReport> result;
  result.reserve(reports.size());
  while (!reports.empty()) {
    result.emplace_back(reports.front());
    reports.pop();
  }
  return result;
}

void AsyncNetworkServer::BackgroudThread() {
  InitializeSocket();
  while (!exit_signal_) {
    report_queue_out_mutex_.lock();
    if (report_queue_out_.size()) {
      SocketSend(report_queue_out_.front());
      report_queue_out_.pop();
    }
    report_queue_out_mutex_.unlock();

    report_queue_in_mutex_.lock();
    MessageReport report;
    if (SocketReceive(report)) {
      report_queue_in_.emplace(report);
    }
    report_queue_in_mutex_.unlock();
  }
}
