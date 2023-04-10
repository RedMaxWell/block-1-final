#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "message.hpp"

class User
{
private:
  const std::string _login;
  std::string _password;
  std::vector <Message> messages;
  
public:
  User(std::string& login, std::string& password);
  ~User() = default;

  const std::string& getLogin() const;

  void printMessages() const;
  void addMessage(Message& message);

  bool checkUser(std::string& login, std::string& password) const;
};
