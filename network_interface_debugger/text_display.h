#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <QPlainTextEdit>
#include "abstract_socket.h"

enum class TextType {
  received, sent, unknown,
};

class TextDisplay
{
public:
  TextDisplay();
  void SetUITextEdit(QPlainTextEdit *ui_text_edit);
  void DisplayMessageReport(
      const MessageReport& report, const TextType& type = TextType::unknown);
protected:
  QPlainTextEdit& UIPlainTextEdit();
private:
  QPlainTextEdit* ui_text_edit_;
};

#endif // TEXT_DISPLAY_H
