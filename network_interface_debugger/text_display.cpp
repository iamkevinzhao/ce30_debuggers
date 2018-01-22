#include "text_display.h"
#include <qDebug>

TextDisplay::TextDisplay()
{

}

void TextDisplay::SetUITextEdit(QPlainTextEdit *ui_text_edit) {
  ui_text_edit_ = ui_text_edit;
}


void TextDisplay::DisplayMessageReport(
    const MessageReport& report, const TextType& type) {
  QString type_identifier;
  switch (type) {
  case TextType::received: type_identifier = "[Received]"; break;
  case TextType::sent: type_identifier = "[Sent]"; break;
  default: type_identifier = "";
  }
  QString string;
  string.reserve(report.message.size());
  for (auto& ch : report.message) {
    QChar qch(ch);
    if ((ch > 0) && (qch.isLetterOrNumber() || (qch == '.'))) {
      string.push_back(ch);
    } else {
      string.append("[" + QString(QByteArray(1, ch).toHex()) + "]");
    }
  }
  ui_text_edit_->appendPlainText(
      type_identifier + (type_identifier.isEmpty() ? "" : " ") +
      QString::number(report.stamp.hour()) + ":" +
      QString::number(report.stamp.minute()) + ":" +
      QString::number(report.stamp.second()) + ":" +
      QString::number(report.stamp.msec()) + " " + string);
}

QPlainTextEdit& TextDisplay::UIPlainTextEdit() {
  return *ui_text_edit_;
}
