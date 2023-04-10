#include "user.hpp"

User::User(std::string& login, std::string& password) : _login(login), _password(password)
{};

const std::string& User::getLogin() const
{
  return _login;
}

void User::printMessages() const
{
  std::cout << "---------Private Messages----------" << std::endl;
  for(int i = 0; i < messages.size(); ++i)
    {
      messages[i].print();
    }
  std::cout << "-----------------------------------" << std::endl;
  return;
}

void User::addMessage(Message& message)
{
  messages.push_back(message);
  return;
}

bool User::checkUser(std::string& login, std::string& password) const
{
  if ((_login == login) && (_password == password))
    return true;
  else
    return false;
}
