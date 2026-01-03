#ifndef EXPORTER_H
#define EXPORTER_H
#include <string>
#include <vector>

#include "Common.h"

class Exporter {
 public:
  static void saveToJson(const std::string& ip, const std::vector<PortResult>& results);
  static void saveToText(const std::string& ip, const std::vector<PortResult>& results);
};
#endif
