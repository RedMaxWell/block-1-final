#include "message.hpp"

Message::Message(std::string& from, std::string& text) : _from(from), _text(text)
{};

const std::string& Message::getMessage() const
{
  return _text;
}

void Message::print() const
{
  std::cout << _from << ": " << _text << std::endl;
  return;
}
