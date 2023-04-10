#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "message.hpp"
#include "user.hpp"

class LoginOccupied : public std::exception
{
  const char* what() const noexcept override
  {
    std::cout << "\a";
    return "Error: this login is occupied";
  }
};

class Server
{
private:
  std::string _name;
  bool _works;

  std::vector <Message>  messages;
  std::vector <User> users;

  User* active_user = nullptr;
public:
  explicit Server(std::string& name);
  ~Server() = default;

  void start();
  void shutdown();

  const std::string& getName() const;

  void setName(std::string& name);
  bool ifWorks() const;

  void addMessage(std::string& from, std::string& text);
  void sendPrivate();//переваривать приватные сообщения "на лету" оказалось очень громоздко, поэтому я просто выделил отдельную функцию для этой цели
  
  void addUser();

  void showMessages() const;
  void showPrivate() const;
  void showUsers() const;

  void login();
  void logout();

  void processMessage();
  void clear() const;
};
