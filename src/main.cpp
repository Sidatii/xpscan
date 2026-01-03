#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <regex>
#include <string>

#include "../include/Exporter.h"
#include "../include/Printer.h"
#include "../include/Scanner.h"

using namespace std;

#define THREAD_NUM 200

void print_usage() {
  std::cout << "Usage: xpscan <IP> [options]\n"
            << "Options:\n"
            << "  --help    Print this message\n"
            << "  --json    Export results to [IP].json\n"
            << "  --txt     Export results to [IP].txt\n"
            << "  --full    Scan all 65535 ports\n";
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
    std::cerr << "\033[31m[x] Invalid IP address format.\033[0m\n";
    return 1;
  }
  struct UserInput input{};
  std::vector<std::string> args(argv + 2, argv + argc);
  input.ip = argv[1];

  // Parse Flags
  bool exportJson = (find(args.begin(), args.end(), "--json") != args.end());
  bool exportTxt = (find(args.begin(), args.end(), "--txt") != args.end());
  bool fullScan = (find(args.begin(), args.end(), "--full") != args.end());

  Printer::printHeader();

  if (fullScan) {
    input.start_port = 1;
    input.end_port = 65535;
  } else {
    std::cout << "\033[36mEnter start port:\033[0m ";
    std::cin >> input.start_port;
    std::cout << "\033[36mEnter end port:\033[0m ";
    std::cin >> input.end_port;
  }
  // cout << "\nEnter the path to save the result (default: " << SAVE_PATH << ")" << ", click enter to use default.\nPath: ";
  // cin >> input.path_choice;
  // if (input.path_choice == "\n") {
  // }

  Scanner scanner(input.ip, THREAD_NUM);
  // Start time recording
  auto start = std::chrono::steady_clock::now();
  scanner.scanRange(input.start_port, input.end_port);
  auto end = std::chrono::steady_clock::now();

  std::chrono::duration<double> diff = end - start;
  std::cout << "\n\033[36m[!] Scan finished in " << diff.count() << "s\033[0m" << std::endl;

  if (exportJson) Exporter::saveToJson(input.ip, scanner.getResults());
  if (exportTxt) Exporter::saveToText(input.ip, scanner.getResults());

  if (!exportJson && !exportTxt) {
    std::cout << "\033[33m[!] No export flags set. Use --json or --txt to save results.\033[0m" << std::endl;
  }

  return 0;
}
