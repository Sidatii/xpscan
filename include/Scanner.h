#ifndef SCANNER_H
#define SCANNER_H

#include <mutex>
#include <string>
#include <vector>

#include "Common.h"

using namespace std;

class Scanner {
 public:
  // constructor
  Scanner(std::string ip, int threads);
  void scanRange(int start, int end);
  std::vector<PortResult> getResults();

 private:
  void scanPort(int port);

  std::string target_ip;
  int max_threads;
  std::vector<PortResult> results;
  std::mutex result_mutex;
};

#endif
