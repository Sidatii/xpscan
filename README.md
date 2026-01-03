<p align="center">
  <img src="assets/xpscan_logo.png" alt="xpscan logo" width="400">
</p>

# XP-SCAN

A high-performance, multithreaded TCP port scanner for Linux.


## Demo

<p align="center">
  <img src="assets/pic1.png" alt="xpscan screen 1">
</p>
---------------------

<p align="center">
  <img src="assets/pic2.png" alt="xpscan screen 2">
</p>

## Authors

- [@sidatii](https://www.github.com/sidatii)


## Features

- Open ports and service names
- Custom port range scanning
- Full port range scanning
- Json and text export format


## Installation

Install xpscan using curl

```bash
curl -sSL https://raw.githubusercontent.com/Sidatii/xpscan/refs/heads/master/install.sh | bash
```


## Run Locally

Clone the project

```bash
  git clone https://github.com/Sidatii/xpscan
```

Go to the project directory

```bash
  cd xpscan
```

Make build directory

```bash
  mkdir build && cd build
```

Compile the project

```bash
  cmake ..
```

```bash
  make
```
Run the binary

```bash
  ./xpscan
```
## Usage/Examples

```bash
xpscan <IP> [OPTIONS]
```

```bash
# No args -> interactive session
xpscan 8.8.8.8 

# Full range scan
xpscan 8.8.8.8 --full

# Export result to json/txt
xpscan 8.8.8.8 --full --json
xpscan 8.8.8.8 --full --txt

```


## Tech Stack

**Dev:** C++

**Build:** cMake, Make

