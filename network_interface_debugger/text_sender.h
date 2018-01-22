#ifndef TEXT_SENDER_H
#define TEXT_SENDER_H

#include <QPlainTextEdit>
#include "text_display.h"
#include <QLineEdit>
#include <QPushButton>

class TextSender : public TextDisplay
{
public:
  TextSender();
  void SetUILineEdit(QLineEdit* line_edit);
  QString GetMessageString();
  void SetMessageWrapFlag(const bool& wrap_on);
  void WrapMessageNow();
private:
  QLineEdit* line_edit_;
  QPushButton* wrap_push_button_;
  bool alway_wrap_on_;
  int bytes_wrap_to_;
};

#endif // TEXT_SENDER_H
