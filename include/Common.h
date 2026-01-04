#ifndef COMMON_H
#define COMMON_H

#include <string>
using namespace std;

struct PortResult
{
    int    port;
    string service;
};

#define START_PORT 1
#define END_PORT 65535
#define RED "\033[31m"
#define BLUE "\033[36m"
#define PINK "\033[33m"
#define NC "\033[0m"

#endif // !COMMON_H
