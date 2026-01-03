#!/bin/bash

# Define colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${BLUE}== xpscan (Pro-Scanner) Installer ==${NC}"

# 1. Check for dependencies
for cmd in git cmake g++; do
  if ! command -v $cmd &>/dev/null; then
    echo -e "${RED}[!] Error: $cmd is not installed.${NC}"
    exit 1
  fi
done

# 2. Setup Configuration
read -p "Enter default export directory [default: ~/xpscan/]: " EXPORT_PATH
EXPORT_PATH=${EXPORT_PATH:-$HOME/xpscan/}

mkdir -p "$EXPORT_PATH"
CONFIG_DIR="$HOME/.config/.xpscan"
mkdir -p "$CONFIG_DIR"
echo "$EXPORT_PATH" >"$CONFIG_DIR/path.conf"

# 3. Clone and Build
TEMP_DIR=$(mktemp -d)
echo -e "${BLUE}[*] Cloning repository to $TEMP_DIR...${NC}"

git clone https://github.com/sidatii/xpscan.git $TEMP_DIR
cd $TEMP_DIR

echo -e "${BLUE}[*] Compiling...${NC}"
mkdir build && cd build
cmake .. && make

# 4. Install
if [ -f "xpscan" ]; then
  sudo mv xpscan /usr/local/bin/xpscan
  echo -e "${GREEN}[+] xpscan installed successfully to /usr/local/bin/xpscan${NC}"
else
  echo -e "${RED}[!] Build failed.${NC}"
  exit 1
fi

# 5. Cleanup
cd /tmp
rm -rf "$TEMP_DIR"

echo -e "${GREEN}[+] Done! Run 'xpscan --help' to get started.${NC}"
