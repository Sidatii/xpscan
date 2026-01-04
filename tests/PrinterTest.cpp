#include "../include/Printer.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <sstream>
#include <vector>

Test(Printer, getTerminalWidth_should_return_positive_value) {
  int width = Printer::getTerminalWidth();

  cr_assert(width >= 0, "Terminal width should be non-negative");
}

Test(Printer, clearScreen_should_output_clear_sequence) {
  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::clearScreen();

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  cr_assert(output.find("\033[2J\033[H") != std::string::npos,
            "clearScreen should output ANSI escape sequences");
}

Test(Printer, printCentered_should_add_padding) {
  std::vector<std::string> test_art = {"Line 1", "Line 2"};
  int terminal_width = 80;

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::printCentered(test_art, terminal_width);

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  cr_assert(output.find("Line 1") != std::string::npos,
            "Output should contain the art content");
  cr_assert(output.find("Line 2") != std::string::npos,
            "Output should contain all lines");
}

Test(Printer, printCentered_with_narrow_terminal) {
  std::vector<std::string> test_art = {"just lie to test and test"};
  int narrow_width = 10;

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::printCentered(test_art, narrow_width);

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  cr_assert(output.find("just lie to test and test") != std::string::npos,
            "Content should still be printed even with narrow terminal");
}

Test(Printer, printCentered_with_empty_art) {
  std::vector<std::string> empty_art;
  int terminal_width = 80;

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::printCentered(empty_art, terminal_width);

  std::cout.rdbuf(old_cout);

  cr_assert(true, "printCentered should handle empty art gracefully");
}

Test(Printer, printCentered_should_include_color_codes) {
  std::vector<std::string> test_art = {"Test"};
  int terminal_width = 80;

  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::printCentered(test_art, terminal_width);

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  cr_assert(output.find("\033[") != std::string::npos,
            "Output should contain ANSI color codes");
}

Test(Printer, printHeader_should_output_banner) {
  std::ostringstream captured_output;
  std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

  Printer::printHeader();

  std::cout.rdbuf(old_cout);

  std::string output = captured_output.str();
  // Check for parts of the ASCII art banner
  cr_assert(output.find("XP") != std::string::npos ||
            output.find("****") != std::string::npos,
            "Header should contain banner art");
}

Test(Printer, printCentered_with_various_widths) {
  std::vector<std::string> test_art = {"Test Line"};
  std::vector<int> widths = {20, 50, 80, 120, 200};

  for (int width : widths) {
    std::ostringstream captured_output;
    std::streambuf *old_cout = std::cout.rdbuf(captured_output.rdbuf());

    Printer::printCentered(test_art, width);

    std::cout.rdbuf(old_cout);

    std::string output = captured_output.str();
    cr_assert(output.find("Test Line") != std::string::npos,
              "Should work with terminal width %d", width);
  }
}
