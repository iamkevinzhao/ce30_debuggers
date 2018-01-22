#include "main_window.h"
#include "ui_main_window.h"
#include <QDebug>
#include "udp_socket.h"
#include <QMessageBox>
#include <iostream>
#include <QThread>

using namespace std;

const QString kWarnDialogTitle = "Warn";
const QString kErrorDialogTitle = "Error";

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  SetUISocketOptionUDP();
  SetSocketFromUI();
  text_sender_.reset(new TextSender);
  text_sender_->SetUITextEdit(ui->SenderPlainTextEdit);
  text_receiver_.reset(new TextReceiver);
  text_receiver_->SetUITextEdit(ui->ReceiverPlainTextEdit);
  timer_id_ = startTimer(100);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timer_id_) {
    auto reports = socket_->AsyncReceive();
    if (reports.empty()) {
      return;
    }
    for (auto& report : reports) {
      text_receiver_->DisplayMessageReport(report, TextType::received);
    }
  }
}

void MainWindow::SetUISocketOptionTCP() {
  ui->TCPCheckBox->setChecked(true);
  ui->UDPCheckBox->setChecked(false);
}

void MainWindow::SetUISocketOptionUDP() {
  ui->TCPCheckBox->setChecked(false);
  ui->UDPCheckBox->setChecked(true);
}

void MainWindow::SetSocketFromUI() {
  // socket_.reset();
  if (ui->TCPCheckBox->isChecked()) {
    QMessageBox::information(
        this, kWarnDialogTitle,
        "UDP socket is currently not supported.", QMessageBox::Ok);
    SetUISocketOptionUDP();
    socket_.reset(new UDPSocket);
    socket_->Initialize();
  } else if (ui->UDPCheckBox->isChecked()) {
    socket_.reset(new UDPSocket);
    socket_->Initialize();
  } else {
    QMessageBox::critical(
        this, kErrorDialogTitle,
        "Neither UDP nor TCP is selected, setting UDP socket as default.",
        QMessageBox::Ok);
    SetUISocketOptionUDP();
    socket_.reset(new UDPSocket);
    socket_->Initialize();
  }
}

void MainWindow::on_TCPCheckBox_clicked()
{
  ui->UDPCheckBox->setChecked(!ui->TCPCheckBox->isChecked());
  SetSocketFromUI();
}

void MainWindow::on_UDPCheckBox_clicked()
{
  ui->TCPCheckBox->setChecked(!ui->UDPCheckBox->isChecked());
  SetSocketFromUI();
}

void MainWindow::on_SendPushButton_clicked()
{
  if (!socket_) {
    cerr << "No socket has been established." << endl;
    QApplication::exit(-1);
  }
  text_sender_->DisplayMessageReport(
      socket_->Send(text_sender_->GetMessageString()), TextType::sent);
}
