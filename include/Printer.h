#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>

using namespace std;

struct UserInput {
  string ip;
  int start_port;
  int end_port;
};

class Printer {
 public:
  static int getTerminalWidth();
  static void printCentered(const vector<string>& art, int terminalWidth);
  static void printHeader();
  static void clearScreen();
};
#endif  // !PRINTER_H
