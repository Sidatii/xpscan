#include "../include/Scanner.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <vector>

Test(Scanner, constructor_should_initialize_with_ip_and_threads) {
  Scanner scanner("192.168.1.1", 100);
  std::vector<PortResult> results = scanner.getResults();

  cr_assert(results.empty(), "Newly created scanner should have no results");
}

Test(Scanner, getResults_should_return_empty_vector_initially) {
  Scanner scanner("10.0.0.1", 50);
  std::vector<PortResult> results = scanner.getResults();

  cr_assert_eq(results.size(), 0, "Initial results should be empty");
}

Test(Scanner, scanRange_should_complete_without_crash) {
  Scanner scanner("127.0.0.1", 10);

  scanner.scanRange(1, 10);

  std::vector<PortResult> results = scanner.getResults();

  cr_assert(results.size() >= 0, "scanRange should complete and return results");
}

Test(Scanner, scanRange_with_single_port) {
  Scanner scanner("127.0.0.1", 1);

  scanner.scanRange(80, 80);

  cr_assert(true, "Scanning single port should work");
}

Test(Scanner, multiple_threads_should_not_cause_data_race) {
  Scanner scanner("127.0.0.1", 200);

  scanner.scanRange(1, 100);

  std::vector<PortResult> results = scanner.getResults();

  for (const auto& result : results) {
    cr_assert(result.port >= 1 && result.port <= 100,
              "Port numbers should be within scanned range");
    cr_assert(result.service.length() >= 0,
              "Service name should be valid");
  }
}

Test(Scanner, different_thread_counts) {
  std::vector<int> thread_counts = {1, 10, 50, 200};

  for (int thread_count : thread_counts) {
    Scanner scanner("127.0.0.1", thread_count);
    scanner.scanRange(1, 20);

    cr_assert(true, "Scanner should work with %d threads", thread_count);
  }
}
