#include "../include/Exporter.h"

#include <cstddef>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

Exporter::Exporter(const std::string& config_path) : config_path_(config_path) {}

std::string Exporter::getExportPath() {
  std::string config_file = config_path_.empty()
    ? std::string(getenv("HOME")) + "/.config/.xpscan/path.conf"
    : config_path_;

  std::ifstream file(config_file);
  if (!file.is_open()) {
    std::cout << "[x] Error opening config file...";
    return NULL;
  }
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

// Helper to get formatted time
std::string get_current_time_str() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}

void Exporter::saveToJson(const std::string& ip, const std::vector<PortResult>& results) {
  if (results.empty()) {
    return;
  }
  std::string dir = getExportPath();
  std::string full_path = dir + ip + "_" + get_timestamp() + ".json";

  std::ofstream file(full_path);
  file << "{\n";
  file << "  \"metadata\": {\n";
  file << "    \"tool\": \"xpscan\",\n";
  file << "    \"version\": \"1.0.0\",\n";
  file << "    \"date\": \"" << get_current_time_str() << "\",\n";
  file << "    \"target\": \"" << ip << "\",\n";
  file << "    \"open_ports_count\": " << results.size() << "\n";
  file << "  },\n";
  file << "  \"results\": [\n";

  for (size_t i = 0; i < results.size(); ++i) {
    file << "    {\"port\": " << results[i].port << ", \"service\": \"" << results[i].service << "\"}";
    if (i < results.size() - 1) file << ",";
    file << "\n";
  }

  file << "  ]\n";
  file << "}\n";
  std::cout << "\033[34m[*] JSON metadata included. Saved to: " << full_path << "\033[0m" << std::endl;
}

void Exporter::saveToText(const std::string& ip, const std::vector<PortResult>& results) {
  if (results.empty()) {
    std::cout << "\033[34m[x] No results found, skipping export." << "\033[0m" << std::endl;
    return;
  }
  std::string dir = getExportPath();
  std::string full_path = dir + ip + "_" + get_timestamp() + ".txt";

  std::ofstream file(full_path);
  file << "==========================================\n";
  file << " xpscan Report\n";
  file << "==========================================\n";
  file << "Target IP  : " << ip << "\n";
  file << "Date       : " << get_current_time_str() << "\n";
  file << "Tool Ver   : 1.0.0\n";
  file << "Total Open : " << results.size() << "\n";
  file << "------------------------------------------\n\n";

  for (const auto& res : results) {
    file << "[+] Port " << std::left << std::setw(6) << res.port
         << " | Service: " << res.service << "\n";
  }
  std::cout << "\033[34m[*] TXT metadata included. Saved to: " << full_path << "\033[0m" << std::endl;
}
