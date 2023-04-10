#include <memory>

#include "user.hpp"
#include "message.hpp"
#include "server.hpp"

int main()
{
  std::cout << "Wellcome to server 0.1!" << std::endl;
  std::string server_name;
  std::cout << "Enter server name: ";
  std::getline(std::cin, server_name);

  std::string& name = server_name; // костыль по моему, не нашел как в данном случае инициировать сервер. Либо так, либо убрать explicit
  Server server(name);
  server.start();
  
  std::cout << "type /help to see the list of commands" << std::endl;
  
  while (server.ifWorks())
    {
      server.processMessage();
    }

  return 0;
}
