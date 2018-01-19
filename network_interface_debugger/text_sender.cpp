#include "text_sender.h"

TextSender::TextSender()
{

}

void TextSender::SetUITextEdit(QPlainTextEdit *ui_text_edit) {
  ui_text_edit_ = ui_text_edit;
}

QString TextSender::GetMessageString() {
  auto string = ui_text_edit_->toPlainText();
  ui_text_edit_->clear();
  return string;
}
