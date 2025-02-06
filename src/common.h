#ifndef COMMON_H
#define COMMON_H

#include <string>

struct Message {
  std::string topic;
  std::string payload;
  bool isAlert;
};

#endif