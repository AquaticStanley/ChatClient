#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdlib>

class Config
{
private:
  std::unordered_map<std::string, std::string> config;

public:
  Config(std::string configFilename);

  std::string operator[](std::string index);
};