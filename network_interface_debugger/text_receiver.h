#ifndef TEXT_RECEIVER_H
#define TEXT_RECEIVER_H

#include <QPlainTextEdit>
#include "abstract_socket.h"
#include "text_display.h"

class TextReceiver : public TextDisplay
{
public:
  TextReceiver();
};

#endif // TEXT_RECEIVER_H
