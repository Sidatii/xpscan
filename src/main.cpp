#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <regex>
#include <string>

#include "../include/Exporter.h"
#include "../include/Printer.h"
#include "../include/Scanner.h"

#define START_PORT 1
#define END_PORT 65535
#define RED "\033[31m"
#define BLUE "\033[36m"
#define PINK "\033[33m"
#define NC "\033[0m"

using namespace std;

#define THREAD_NUM 200

void print_usage() {
  std::cout << PINK << "Usage: xpscan <IP> [options]\n"
            << NC
            << BLUE << "Options:\n"
            << "  --help    Print this message\n"
            << "  --json    Export results to [IP].json\n"
            << "  --txt     Export results to [IP].txt\n"
            << "  --full    Scan all 65535 ports\n"
            << NC;
}

int main(int argc, char* argv[]) {
  // check if at least one arg is passed
  if (argc < 2 || std::strcmp(argv[1], "--help") == 0) {
    print_usage();
    return 1;
  }

  // Validate the ip
  std::regex ip_regex(R"(^(\d{1,3}\.){3}\d{1,3}$)");
  if (!std::regex_match(argv[1], ip_regex)) {
    std::cerr << RED << "[x] Invalid IP address format." << NC << endl;
    return 1;
  }

  // Instatiate user input struct
  struct UserInput input{};

  // Parse args
  std::vector<std::string> args(argv + 2, argv + argc);

  // Set IP attribute to the second arg passed
  input.ip = argv[1];

  // Parse Flags
  bool exportJson = (find(args.begin(), args.end(), "--json") != args.end());
  bool exportTxt = (find(args.begin(), args.end(), "--txt") != args.end());
  bool fullScan = (find(args.begin(), args.end(), "--full") != args.end());

  Printer::printHeader();

  // Check for fullscan flag
  if (fullScan) {
    input.start_port = START_PORT;
    input.end_port = END_PORT;
  } else {
    std::cout << BLUE << "Enter start port:" << NC;
    std::cin >> input.start_port;
    std::cout << BLUE << "Enter end port:" << NC;
    std::cin >> input.end_port;
  }

  // Instatiate the scanner class with params
  Scanner scanner(input.ip, THREAD_NUM);

  // Record start time
  auto start = std::chrono::steady_clock::now();

  // Proceed with the scanning logic
  scanner.scanRange(input.start_port, input.end_port);

  // Record end time
  auto end = std::chrono::steady_clock::now();

  // Calculate elapsed time
  std::chrono::duration<double> diff = end - start;
  std::cout << "\n"
            << BLUE << "[!] Scan finished in " << diff.count() << "s" << NC << std::endl;

  Exporter exporter;  // Uses default config path because i extracted the config file path as a parameter
  if (exportJson) exporter.saveToJson(input.ip, scanner.getResults());
  if (exportTxt) exporter.saveToText(input.ip, scanner.getResults());

  if (!exportJson && !exportTxt) {
    std::cout << PINK << "[!] No export flags set. Use --json or --txt to save results." << NC << std::endl;
  }

  return 0;
}
