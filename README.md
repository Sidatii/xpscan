# Pro-Scanner CLI
A high-performance, multithreaded TCP port scanner for Linux.

## Features
- **Asynchronous Scanning:** Uses non-blocking sockets for speed.
- **Service Detection:** Identifies services via `/etc/services`.
- **JSON Export:** Automatically saves results to `[IP].json`.
- **Real-time Progress:** Live CLI feedback with timers.

## Project Structure

```Plaintext
ProScanner/
├── CMakeLists.txt          # Build instructions
├── README.md               # Project documentation
├── include/                # Header files (.h)
│   ├── Scanner.h           # Network logic definitions
│   ├── Exporter.h          # Format saving definitions
│   ├── Printer.h           # CLI easthitics
│   └── Common.h            # Shared structs (e.g., PortResult)
└── src/                    # Source files (.cpp)
    ├── main.cpp            # CLI loop and user input
    ├── Scanner.cpp         # Socket logic (non-blocking)
    ├── Printer.cpp         # CLI easthitics
    └── Exporter.cpp        # File I/O logic
```


## Installation

```bash
mkdir build && cd build
cmake ..
make
./pro-scanner
```
