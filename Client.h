#pragma once

#include <iostream>
#include <netdb.h>
#include <thread>
#include <cstdlib>
#include <exception>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <limits>
#include "Config.h"

const int MAX_MESSAGE_LENGTH = 768;
const int MAX_USERNAME_LENGTH = 256;

class Client
{
private:
  std::string username;

public:
  Client(Config config);

  void reader(int socket_descriptor);

  std::string getUsername() { return username; }
};