#include "../include/Exporter.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

std::string get_export_path() {
  std::string config_file = std::string(getenv("HOME")) + "/.config/.xpscan/path.conf";
  std::ifstream file(config_file);
  std::string path;
  if (file >> path) return path;
  return std::string(getenv("HOME")) + "/xpscan/";  // Fallback
}

std::string get_timestamp() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
  return oss.str();
}

void Exporter::saveToJson(const std::string& ip, const std::vector<PortResult>& results) {
  if (results.empty()) {
    std::cout << "\033[34m[x] No results found, skipping export." << "\033[0m" << std::endl;
    return;
  }
  std::string dir = get_export_path();
  std::string full_path = dir + "/" + ip + "_" + get_timestamp() + ".json";

  std::ofstream file(full_path);
  file << "[\n";
  for (size_t i = 0; i < results.size(); ++i) {
    file << "  {\"port\": " << results[i].port << ", \"service\": \"" << results[i].service << "\"}";
    if (i < results.size() - 1) file << ",";
    file << "\n";
  }
  file << "]\n";
  std::cout << "\033[34m[*] Results saved to: " << full_path << "\033[0m" << std::endl;
}

void Exporter::saveToText(const std::string& ip, const std::vector<PortResult>& results) {
  if (results.empty()) {
    std::cout << "\033[34m[x] No results found, skipping export." << "\033[0m" << std::endl;
    return;
  }
  std::string dir = get_export_path();
  std::string full_path = dir + "/" + ip + "_" + get_timestamp() + ".txt";

  std::ofstream file(full_path);
  file << "[\n";
  for (size_t i = 0; i < results.size(); ++i) {
    file << "Port: " << results[i].port << " | service: " << results[i].service << "\n";
  }
  std::cout << "\033[34m[*] Results saved to: " << full_path << "\033[0m" << std::endl;
}
