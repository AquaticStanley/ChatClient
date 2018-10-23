#include <iostream>
#include "Client.h"
#include "Config.h"

using std::cerr;
using std::cout;
using std::endl;

int main()
{
  Config config("Profile.cfg");
  try
  {
    Client client(config);
  }
  catch(std::exception& e)
  {
    cerr << e.what() << endl;
    return 1;
  }
}