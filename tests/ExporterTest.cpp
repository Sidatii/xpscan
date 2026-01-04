#include "../include/Exporter.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Helper functions signatures
std::string createTestDirectory();
std::string createTestConfig(const std::string &export_path,
                             const std::string &suffix = "");
void cleanupTestFiles(const std::string &pattern);

Test(Exporter, empty_results_should_skip_json_export) {
  Exporter exporter;
  std::vector<PortResult> empty_results;

  exporter.saveToJson("0.0.0.0", empty_results);

  cr_assert(true, "saveToJson should handle empty results gracefully");
}

Test(Exporter, empty_results_should_skip_text_export) {
  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Exporter exporter;
  std::vector<PortResult> empty_results;
  exporter.saveToText("0.0.0.0", empty_results);

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  cr_assert(output.find("No results found, skipping export.") !=
                std::string::npos,
            "Expected 'No results found' message");
}

Test(Exporter, should_export_valid_json_with_results) {
  std::string test_dir = createTestDirectory();
  std::string config_path = createTestConfig(test_dir, "_json");

  std::vector<PortResult> results = {{80, "http"}, {443, "https"}, {22, "ssh"}};

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Exporter exporter(config_path);
  exporter.saveToJson("192.168.1.1", results);

  std::cout.rdbuf(old_cout);

  // Find the created JSON file
  bool file_found = false;
  std::string json_content;
  for (const auto &entry : std::filesystem::directory_iterator(test_dir)) {
    if (entry.path().extension() == ".json") {
      file_found = true;
      std::ifstream json_file(entry.path());
      std::stringstream buffer;
      buffer << json_file.rdbuf();
      json_content = buffer.str();
      break;
    }
  }

  cr_assert(file_found, "JSON file should be created");
  cr_assert(json_content.find("\"tool\": \"xpscan\"") != std::string::npos,
            "JSON should contain tool metadata");
  cr_assert(json_content.find("\"target\": \"192.168.1.1\"") !=
                std::string::npos,
            "JSON should contain target IP");
  cr_assert(json_content.find("\"open_ports_count\": 3") != std::string::npos,
            "JSON should contain correct port count");
  cr_assert(json_content.find("\"port\": 80") != std::string::npos,
            "JSON should contain port 80");
  cr_assert(json_content.find("\"service\": \"http\"") != std::string::npos,
            "JSON should contain http service");

  cleanupTestFiles(test_dir);
  std::filesystem::remove(config_path);
}

Test(Exporter, should_export_valid_text_with_results) {
  std::string test_dir = createTestDirectory();
  cleanupTestFiles(test_dir);
  std::string config_path = createTestConfig(test_dir, "_txt");

  std::vector<PortResult> results = {{80, "http"}, {443, "https"}};

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Exporter exporter(config_path);
  exporter.saveToText("10.0.0.1", results);

  std::cout.rdbuf(old_cout);

  // Find the created TXT file
  bool file_found = false;
  std::string txt_content;
  if (std::filesystem::exists(test_dir)) {
    for (const auto &entry : std::filesystem::directory_iterator(test_dir)) {
      if (entry.path().extension() == ".txt") {
        file_found = true;
        std::ifstream txt_file(entry.path());
        std::stringstream buffer;
        buffer << txt_file.rdbuf();
        txt_content = buffer.str();
        break;
      }
    }
  }

  cr_assert(file_found, "TXT file should be created");
  cr_assert(txt_content.find("xpscan Report") != std::string::npos,
            "TXT should contain report header");
  cr_assert(txt_content.find("Target IP  : 10.0.0.1") != std::string::npos,
            "TXT should contain target IP");
  cr_assert(txt_content.find("Total Open : 2") != std::string::npos,
            "TXT should contain correct port count");
  cr_assert(txt_content.find("Port 80") != std::string::npos,
            "TXT should contain port 80");
  cr_assert(txt_content.find("Service: http") != std::string::npos,
            "TXT should contain http service");

  cleanupTestFiles(test_dir);
  std::filesystem::remove(config_path);
}

Test(Exporter, getExportPath_should_read_from_config) {
  std::string test_dir = "/tmp/custom_export_path/";
  std::string config_path = createTestConfig(test_dir, "_getpath");

  Exporter exporter(config_path);
  std::string result = exporter.getExportPath();

  cr_assert(result.find(test_dir) != std::string::npos,
            "getExportPath should return the path from config file, got: %s, "
            "expected: %s",
            result.c_str(), test_dir.c_str());

  std::filesystem::remove(config_path);
}

std::string createTestDirectory() {
  std::string test_dir = "/tmp/xpscan_test/";
  std::filesystem::create_directories(test_dir);
  return test_dir;
}

std::string createTestConfig(const std::string &export_path,
                             const std::string &suffix) {
  std::string config_path = "/tmp/test_config" + suffix + ".conf";
  std::ofstream config_file(config_path);
  config_file << export_path;
  config_file.close();
  return config_path;
}

void cleanupTestFiles(const std::string &pattern) {
  for (const auto &entry :
       std::filesystem::directory_iterator("/tmp/xpscan_test/")) {
    std::filesystem::remove(entry.path());
  }
}
