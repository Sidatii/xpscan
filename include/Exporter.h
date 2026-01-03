#ifndef EXPORTER_H
#define EXPORTER_H
#include <string>
#include <vector>

#include "Common.h"

class Exporter {
 public:
  Exporter(const std::string& config_path = "");
  void saveToJson(const std::string& ip, const std::vector<PortResult>& results);
  void saveToText(const std::string& ip, const std::vector<PortResult>& results);
  std::string getExportPath();

 private:
  std::string config_path_;
};
#endif
