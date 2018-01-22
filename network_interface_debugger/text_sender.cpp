#include "text_sender.h"

TextSender::TextSender()
  : alway_wrap_on_(false), bytes_wrap_to_(50)
{

}

void TextSender::SetUILineEdit(QLineEdit *line_edit) {
  line_edit_ = line_edit;
}

QString TextSender::GetMessageString() {
  if (alway_wrap_on_) {
    WrapMessageNow();
  }
  auto string = line_edit_->text();
  line_edit_->clear();
  return string;
}

void TextSender::SetMessageWrapFlag(const bool &wrap_on) {
  alway_wrap_on_ = wrap_on;
}

void TextSender::WrapMessageNow() {
  auto string = line_edit_->text();
  if (string.size() > bytes_wrap_to_) {
    string.chop(string.size() - bytes_wrap_to_);
  } else if (!string.isEmpty()) {
    string.append(QString(bytes_wrap_to_ - string.size(), 0));
  }
  line_edit_->clear();
  line_edit_->setText(string);
}
