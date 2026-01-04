
---

# Contributing to xpscan 🚀

First of all, thank you for showing interest in contributing to **xpscan**! Community contributions are what make open-source tools robust and reliable.

Whether you are fixing a bug, improving documentation, or adding a new feature, your help is appreciated. Please take a moment to review this guide to ensure a smooth contribution process.

---

## 🏗️ Project Architecture Overview

Before you dive into the code, it helps to understand how the project is organized. We follow a modular design to keep the networking logic separate from the file management.

* **Scanner:** Handles the networking logic (non-blocking sockets).
* **Exporter:** Handles saving results to the disk.
* **Common:** Shared data structures (like the `PortResult` struct).
* **Tests:** Unit tests using CRITERION to ensure stability.

---

## 🛠️ How to Get Started

### 1. Prerequisites

You will need the following tools on your machine:

* **C++ Compiler** (supporting C++17 or later)
* **CMake** (version 3.10+)
* **Git**
* **Criterion** (usually fetched automatically via CMake)

### 2. Setting Up Your Local Environment

1. **Fork** the repository on GitHub.
2. **Clone** your fork locally:
```bash
git clone https://github.com/your-username/xpscan.git
cd xpscan

```


3. **Build** the project to make sure everything is working:
```bash
mkdir build && cd build
cmake ..
make

```



---

## 🧪 Development Rules

### 1. Writing Tests

We use **Mocking** to test the scanner without actually hitting the network and to test the exporter without actually writing to the disk.

* If you add a new feature, please add a test in `tests/ScannerTest.cpp`.
* Run tests using: `ctest` or `./xpscan_tests`.

### 2. Performance First

`xpscan` is designed to be fast.

* Avoid blocking calls.
* Always use the `O_NONBLOCK` flag for new networking features.
* Respect the 200ms timeout window to prevent the tool from "hanging."

### 3. Code Style

* Use descriptive variable names.
* Comment complex logic, especially around bitwise operations or socket configurations.
* Keep functions small and focused on a single task.

---

## 📬 Submitting Your Changes

### Step 1: Create a Branch

Always create a new branch for your work:

```bash
git checkout -b feature/your-feature-name

```

### Step 2: Commit Your Changes

Write clear, concise commit messages:

* `feat: add XML export support`
* `fix: resolve memory leak in scanner`
* `docs: update installation instructions`

### Step 3: Push and Open a Pull Request (PR)

1. Push your branch to your fork: `git push origin feature/your-feature-name`.
2. Open a Pull Request on the main repository.
3. Fill out the **PR Template** provided (it will pop up automatically).
4. Wait for a maintainer to review your code!

---

## 📜 Code of Conduct

By participating in this project, you agree to maintain a respectful and inclusive environment. Please be kind to other contributors!

---
