#ifndef TEXT_SENDER_H
#define TEXT_SENDER_H

#include <QPlainTextEdit>
#include "text_display.h"

class TextSender : public TextDisplay
{
public:
  TextSender();
  QString GetMessageString();
};

#endif // TEXT_SENDER_H
