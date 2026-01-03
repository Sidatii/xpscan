#!/bin/bash

# Define colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}== XP-SCAN Installer ==${NC}"

# Ask for export path
read -p "Enter default export directory [default: ~/xpscan/]: " EXPORT_PATH
EXPORT_PATH=${EXPORT_PATH:-~/xpscan/}

# Create directories
mkdir -p "$EXPORT_PATH"
CONFIG_DIR="$HOME/.config/.xpscan"
mkdir -p "$CONFIG_DIR"

# Save path to config
echo "$EXPORT_PATH" >"$CONFIG_DIR/path.conf"

# Build the project
echo -e "${BLUE}[*] Compiling...${NC}"
mkdir -p build && cd build
cmake .. && make

# Install binary
sudo mv xpscan /usr/local/bin/xpscan

echo -e "${GREEN}[+] Installation complete!${NC}"
echo -e "${GREEN}[+] You can now run the tool using 'xpscan' command.${NC}"
