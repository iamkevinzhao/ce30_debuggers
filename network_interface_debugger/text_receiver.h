#ifndef TEXT_RECEIVER_H
#define TEXT_RECEIVER_H

#include <QPlainTextEdit>
#include "abstract_socket.h"

enum class TextType {
  received, sent, unknown,
};

class TextReceiver
{
public:
  TextReceiver();
  void SetUITextEdit(QPlainTextEdit* ui_text_edit);
  void DisplayMessageReport(
      const MessageReport& report, const TextType& type = TextType::received);
private:
  QPlainTextEdit* ui_text_edit_;
};

#endif // TEXT_RECEIVER_H
