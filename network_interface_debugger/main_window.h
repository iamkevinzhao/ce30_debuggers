#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "abstract_socket.h"
#include <memory>
#include "text_sender.h"

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

private:
  void SetSocketFromUI();
  void SetUISocketOptionTCP();
  void SetUISocketOptionUDP();
  Ui::MainWindow *ui;
  std::shared_ptr<AbstractSocket> socket_;
  std::shared_ptr<TextSender> text_sender_;
  int timer_id_;
};

#endif // MAIN_WINDOW_H
