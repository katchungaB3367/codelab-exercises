# Smart Vending Machine

A simple **C++17 console-based vending machine simulator**.  
This program allows users to browse items, insert money, make purchases, and receive change.  
Stock is stored in a file (`stock.txt`) so that inventory persists between runs.

---

## Requirements
- A C++17 compatible compiler (e.g., `g++`).
- Windows (UTF-8 console support enabled) or Linux.

---

## Build & Run
```bash
# Compile
g++ -std=c++17 vending_machine.cpp -o SmartVendingMachine.exe

# Run
./SmartVendingMachine.exe

