#include "Client.h"

Client::Client(Config config)
{
  username = config["Username"];

  struct sockaddr_in server_addr = {};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(std::stoi(config["DefaultPort"]));

  // Get the host
  struct hostent* host;
  std::cout << "Client is getting the host...\n";
  std::string duh = "duh";
  if((host = gethostbyname(config["DefaultServer"].c_str())) == NULL)
  {
    throw std::runtime_error("Server failed to locate host");
  }
  bcopy( host->h_addr_list[0], (char*)&server_addr.sin_addr, host->h_length );
  std::cout << "Success!\n\n";

  // Create a socket
  int socket_descriptor;
  std::cout << "Client is creating socket...\n";
  if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    throw std::runtime_error("Client failed to create a socket.");
  }
  std::cout << "Success!\n\n";

  // Connect a socket
  std::cout << "Client is connecting the socket...\n";
  if(connect(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
  {
    throw std::runtime_error("Client failed to connect the socket.");
  }
  std::cout << "Success! A message will be sent to the server.\n\n";


  // Introduce the client to server by passing username
  char buff[MAX_MESSAGE_LENGTH];
  char username_c_str[MAX_USERNAME_LENGTH];

  strcpy(username_c_str, username.c_str());
  write(socket_descriptor, username_c_str, sizeof(username_c_str));

  // Create a thread for reading messages
  std::thread readerThread(&Client::reader, this, socket_descriptor);

  // Constantly write to server
  while(1)
  {
    std::cin.getline(buff, MAX_MESSAGE_LENGTH);
    if(!strcmp(buff, "!quit"))
    {
      std::cout << "Break" << std::endl;
      break;
    }
    write(socket_descriptor, buff, sizeof(buff));
  }

  // Close threads and connections
  std::cout << "Connection will now be closed...\n";
  readerThread.detach();
  close(socket_descriptor);
  std::cout << "Connection is now closed.\n\n";
}

void Client::reader(int socket_descriptor)
{
  // Make this 1024 + 256 probably
  char buff[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH];
}