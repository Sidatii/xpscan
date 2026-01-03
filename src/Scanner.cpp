#include "../include/Scanner.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <thread>

Scanner::Scanner(std::string ip, int threads) : target_ip(ip), max_threads(threads) {}

void Scanner::scanPort(int port) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) return;

  // Set to Non-Blocking mode
  fcntl(sock, F_SETFL, O_NONBLOCK);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  inet_pton(AF_INET, target_ip.c_str(), &addr.sin_addr);

  // In a non blocking context, the return of connect() is neglicted
  // In this case stored to a variable to avoid unexpected behavior
  int connect_output = connect(sock, (struct sockaddr*)&addr, sizeof(addr));

  // Use select to wait exactly 500ms
  fd_set fdset;
  FD_ZERO(&fdset);
  FD_SET(sock, &fdset);
  struct timeval tv;
  tv.tv_sec = 0;
  // 500ms timeout
  tv.tv_usec = 500000;

  if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1) {
    int so_error;
    socklen_t len = sizeof(so_error);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

    if (so_error == 0) {
      struct servent* serv = getservbyport(htons(port), "tcp");
      std::string s_name = (serv) ? serv->s_name : "unknown";

      std::lock_guard<std::mutex> lock(result_mutex);
      results.push_back({port, s_name});
      std::cout << "\r\033[K\033[32m[+] Port " << port << " OPEN (" << s_name << ")\033[0m" << std::endl;
    }
  }
  close(sock);
}

void Scanner::scanRange(int start, int end) {
  std::vector<std::thread> pool;
  for (int p = start; p <= end; ++p) {
    pool.emplace_back(&Scanner::scanPort, this, p);

    if (pool.size() >= max_threads) {
      for (auto& t : pool)
        if (t.joinable()) t.join();
      pool.clear();
      std::cout << "\r\033[33m[*] Scanning: " << p << "/" << end << "...\033[0m" << std::flush;
    }
  }
  for (auto& t : pool)
    if (t.joinable()) t.join();
}

std::vector<PortResult> Scanner::getResults() { return results; }
