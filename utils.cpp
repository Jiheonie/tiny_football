#include <iostream>
#include <string>
#include <sstream>
#include "utils.h"

template <typename T>
std::string itos(T i)
{
  std::stringstream s;
  s << i;
  return s.str();
}