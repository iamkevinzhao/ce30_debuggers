#include "text_sender.h"
#include <QDebug>

TextSender::TextSender()
  : alway_wrap_on_(false), bytes_wrap_to_(50)
{

}

void TextSender::SetUILineEdit(QLineEdit *line_edit) {
  line_edit_ = line_edit;
}

QString TextSender::GetMessageString() {
  auto line_string = line_edit_->text();
  line_edit_->clear();
  QString string, hex;
  string.reserve(line_string.size());
  for (auto& ch : line_string) {
    if (ch == ']') {
      bool ok;
      string.append(unsigned char(hex.toInt(&ok, 16)));
      hex.clear();
    } else if (ch == '[') {
      hex.append("0x");
    } else if (!hex.isEmpty()) {
      hex.append(ch);
    } else {
      string.append(ch);
    }
  }
  if (alway_wrap_on_) {
    WrapMessageNow();
  }
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
