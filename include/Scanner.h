#ifndef SCANNER_H
#define SCANNER_H

#include <mutex>
#include <string>
#include <vector>

#include "Common.h"

using namespace std;

class Scanner
{
  public:
    // constructor
    Scanner(string ip, int threads);
    void                    scanRange(int start, int end);
    std::vector<PortResult> getResults();

  private:
    void scanPort(int port);

    string             target_ip;
    int                max_threads;
    vector<PortResult> results;
    mutex              result_mutex;
};

#endif
