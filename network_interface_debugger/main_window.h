#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "async_network_server.h"
#include <memory>
#include "text_sender.h"
#include "text_receiver.h"
#include "incoming_packet_sampler.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void timerEvent(QTimerEvent *event);

private slots:
  void on_TCPCheckBox_clicked();

  void on_UDPCheckBox_clicked();

  void on_SendPushButton_clicked();

  void on_WrapMessageCheckBox_clicked(bool checked);

  void on_WrapMessagePushButton_clicked();

private:
  void SetSocketFromUI();
  void SetUISocketOptionTCP();
  void SetUISocketOptionUDP();
  Ui::MainWindow *ui;
  std::shared_ptr<AsyncNetworkServer> socket_;
  std::shared_ptr<TextSender> text_sender_;
  std::shared_ptr<TextReceiver> text_receiver_;
  int timer_id_;
  std::shared_ptr<IncomingPacketSampler> sampler_;
};

#endif // MAIN_WINDOW_H
