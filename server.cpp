#include "server.hpp"
#include "commands.hpp"

Server::Server(std::string& name) : _name(name), _works(false)
{}

void Server::start()
{
  _works = true;
  return;
}

void Server::shutdown()
{
  _works = false;
  return;
}

const std::string& Server::getName() const
{
  return _name;
}

void Server::setName(std::string& name)
{
  _name = name;
  return;
}

bool Server::ifWorks() const
{
  return _works;
}

void Server::addMessage(std::string& from, std::string& text)
{
  Message message(from, text);
  messages.push_back(message);
  return;
}

void Server::sendPrivate()
{
  std::string from;
  if (active_user)
    {
      from = active_user->getLogin();
    }
  else
    {
      from = "guest";
    }
  
  std::string to;
  std::cout << "to: ";
  std::getline(std::cin, to);

  for (int i = 0; i < users.size(); ++i)
    {
      if (to == users[i].getLogin())
	{
	  std::string text;
	  std::cout << "message: ";
	  std::getline(std::cin, text);
	  Message message(from, text);
	  users[i].addMessage(message);
	  return;
	}
    }
  std::cout << "No such user as \"" << to << "\"" << std::endl;
}

void Server::addUser()
{
  if (active_user)
    {
      std::cout << "log out first" << std::endl;
      return;
    }
  
  std::string login;
  std::cout << "New User login: ";
  std::getline (std::cin, login);

  for (int i = 0; i < users.size(); ++i)
    {
      if (login == users[i].getLogin())
	{
	  throw LoginOccupied();
	}
    }
  std::string password;
  std::cout << "New User password: ";
  std::getline (std::cin, password);
  User newUser(login, password);
  users.push_back(newUser);

  return;
}

void Server::showMessages() const
{
  std::cout << "----------Public Messages----------" << std::endl;
  for (int i = 0; i < messages.size(); ++i)
    {
      messages[i].print();
    }
  std::cout << "-----------------------------------" << std::endl;
}

void Server::showPrivate() const
{
  if (active_user)
    {
      active_user->printMessages();
      return;
    }
  else
    {
      std::cout << "login first" << std::endl;
      return;
    }
}
void Server::showUsers() const
{
  std::cout << "\n---------------USERS---------------" << std::endl;
  for (int i = 0; i < users.size(); ++i)
    {
      std::cout << users[i].getLogin() << std::endl;
    }
  std::cout << "-----------------------------------\n" << std::endl;
}

void Server::login()
{
  std::string login;
  std::cout << "Login: ";
  std::getline (std::cin, login);

  std::string password;
  std::cout << "Password: ";
  std::getline (std::cin, password);

  for (int i = 0; i < users.size(); ++i)
    {
      if (users[i].checkUser(login, password))
	{
	  active_user = &users[i];
	  std::cout << "wellcome to chat, " << users[i].getLogin() << "!" << std::endl;
	  return;
	}
    }
  std::cout << "wrong login or password" << std::endl;
  return;
}

void Server::logout()
{
  if (active_user)
    {
      active_user = nullptr;
    }
  else
    {
      std::cout << "No active user already" << std::endl;
    }
  return;
}

void Server::processMessage()
{
  if(active_user)
    {
      std::cout << active_user->getLogin() << ": ";
    }
  else
    {
      std::cout << "guest: ";
    }  //это интерфейс
  
  std::string text;
  std::getline(std::cin, text);
  
  if (text[0] == '/') // в этом блоке мы проверяем команда ли данное сообщение. Команды вынесены в отдельный заголовочный файл
    {
      if (text == Clogin)
	{
	  login();
	  return;
	}
      if (text == Clogout)
	{
	  logout();
	  clear();
	  return;
	}
      if (text == Csignup)
	{
	  try
	    {
	      addUser();
	      return;
	    }
	  catch (std::exception& e)
	    {
	      std::cout << e.what() << std::endl;
	      return;
	    }
	}
      if (text == Cshow)
	{
	  showMessages();
	  return;
	}
      if (text == Cusers)
	{
	  showUsers();
	  return;
	}
      if (text == Cwhisper)
	{
	  sendPrivate();
	  return;
	}
      if (text == Cshow_private)
	{
	  showPrivate();
	  return;
	}
      if (text == Chelp)
	{
	  std::cout << "----------Server Commands----------" << std::endl;
	  std::cout << "logIN: /in" << std::endl;
	  std::cout << "logOUT: /out" << std::endl;
	  std::cout << "SIGNIN: /signin" << std::endl;
	  std::cout << "Show public messages: /s" << std::endl;
	  std::cout << "show Users: /u" << std::endl;
	  std::cout << "EXIT programm: /exit" << std::endl;
	  std::cout << "send private message (Whisper): /w" << std::endl;
	  std::cout << "Show Private messages: /sp" << std::endl;
	  std::cout << "show HELP: /help" << std::endl;
	  std::cout << "Clear screen: /c" << std::endl;
	  std::cout << "-----------------------------------" << std::endl;
	  return;
	}
      if (text == Cclear)
	{
	  clear();
	  return;
	}
      if (text == Cexit)
	{
	  _works = false;
	  clear();
	  return;
	}
      else
	{
	  std::cout << "\nUndefined command\n" << std::endl;
	  return;
	}
    }
  else // если сообщение не команда, тогда это просто сообщение и оно отправляется в контейнер
    {
      if (active_user)
	{
	  std::string active_user_login(active_user->getLogin());
	  addMessage(active_user_login, text);
	  return;
	}
      else
	{
	  std::string guest("guest");
	  addMessage(guest, text);
	  return;
	}
    }
}

void Server::clear() const //(типа) очищает экран
{
#if __linux__
  std::cout<< u8"\033[2J\033[1;1H";
  std::cout << "type /help to see the list of commands" << std::endl;
#elif _WIN32
  system("cls");
  std::cout << "type /help to see the list of commands" << std::endl;
#else
  std::cout << "Don't know how to clear on mac(" << std::endl;
#endif
  return;
}
