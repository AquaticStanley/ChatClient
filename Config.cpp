#include "Config.h"

Config::Config(std::string configFilename)
{
  std::ifstream ifs(configFilename);

  if(!ifs)
  {
    throw std::runtime_error("No filepath " + configFilename + " exists.");
  }

  std::string buffer;

  while(ifs >> buffer)
  {
    if(buffer[0] != '\n')
    {
      if(buffer[0] == '[')
      {
        std::string key = buffer.substr(1, buffer.size() - 2);
        ifs >> buffer;
        config[key] = buffer;
      }
    }
  }
}

std::string Config::operator[](std::string index)
{
  return config[index];
}