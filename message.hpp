#pragma once

#include <iostream>
#include <string>

class Message
{
private:
  const std::string _from;
  const std::string _text;
public:
  Message(std::string& from, std::string& text);
  ~Message() = default;

  void print() const;
  const std::string& getMessage() const;
};
