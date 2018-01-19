#ifndef TEXT_SENDER_H
#define TEXT_SENDER_H

#include <QPlainTextEdit>

class TextSender
{
public:
  TextSender();
  void SetUITextEdit(QPlainTextEdit* ui_text_edit);
  QString GetMessageString();
private:
  QPlainTextEdit* ui_text_edit_;
};

#endif // TEXT_SENDER_H
