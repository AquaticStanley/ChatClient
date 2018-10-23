#pragma once

#include <iostream>
#include <netdb.h>
#include <thread>
#include <cstdlib>
#include <exception>
#include <unistd.h>
#include <netdb.h>
#include <limits>
#include "Config.h"

class Client
{
private:
  std::string username;

public:
  Client(Config config);

  void reader(int socket_descriptor);

  std::string getUsername() { return username; }
};