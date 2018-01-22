#include "text_display.h"

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
  default: type_identifier = "[Info]";
  }
  ui_text_edit_->appendPlainText(
      type_identifier + " " +
      QString::number(report.stamp.hour()) + ":" +
      QString::number(report.stamp.minute()) + ":" +
      QString::number(report.stamp.second()) + ":" +
      QString::number(report.stamp.msec()) + " " + report.message);
}

QPlainTextEdit& TextDisplay::UIPlainTextEdit() {
  return *ui_text_edit_;
}
