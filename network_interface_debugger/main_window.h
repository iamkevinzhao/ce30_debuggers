#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "abstract_socket.h"
#include <memory>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

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
};

#endif // MAIN_WINDOW_H
