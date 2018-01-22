#include "text_sender.h"

TextSender::TextSender()
{

}

QString TextSender::GetMessageString() {
  auto string = UIPlainTextEdit().toPlainText();
  UIPlainTextEdit().clear();
  return string;
}
