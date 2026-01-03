#include "../include/Printer.h"

#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using namespace std;

int Printer::getTerminalWidth() {
  // Instantiate a window size struct
  struct winsize w;
  // Setting some magic numbers for file descriptor and request. and passing the window size struct
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  // Returning the width columns
  return w.ws_col;
}

void Printer::clearScreen() {
  // \033[2J clears the screen, \033[H moves cursor to top
  std::cout << "\033[2J\033[H";
}

void Printer::printHeader() {
  Printer::clearScreen();

  std::vector<std::string> myArt = {
      "****************************************************",
      "*              ╻ ╻┏━┓   ┏━┓┏━╸┏━┓┏┓╻               *",
      "*              ┏╋┛┣━┛   ┗━┓┃  ┣━┫┃┗┫               *",
      "*              ╹ ╹╹     ┗━┛┗━╸╹ ╹╹ ╹               *",
      "*   --------------------------------------------   *",
      "*   01101000 01110101 01101101 01100001 01101110   *",
      "*   --------------------------------------------   *",
      "****************************************************\n\n",
  };

  int width = Printer::getTerminalWidth();
  Printer::printCentered(myArt, width);
}

void Printer::printCentered(const vector<string>& art, int terminalWidth) {
  size_t maxWidth = 0;
  const std::string COLOR = "\033[33m";
  const std::string RESET = "\033[0m";

  // Step 1: Find the widest line in the art
  for (const std::string& line : art) {
    maxWidth = std::max(maxWidth, line.length());
  }

  // Step 2: Calculate padding based on the widest line
  int padding = (terminalWidth - (int)maxWidth) / 2;
  if (padding < 0) padding = 0;  // Prevent errors if terminal is too narrow

  // Step 3: Print every line using the SAME padding
  for (const std::string& line : art) {
    std::cout << std::string(padding, ' ') << COLOR << line << RESET << std::endl;
  }
}
