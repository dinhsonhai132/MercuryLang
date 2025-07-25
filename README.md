# 🪐 Mercury Programming Language

![GitHub Stars](https://img.shields.io/github/stars/dinhsonhai132/MercuryLang?style=social)
![GitHub Forks](https://img.shields.io/github/forks/dinhsonhai132/MercuryLang?style=social)
![Repo Size](https://img.shields.io/github/repo-size/dinhsonhai132/MercuryLang)
![Issues](https://img.shields.io/github/issues/dinhsonhai132/MercuryLang)
![License](https://img.shields.io/github/license/dinhsonhai132/MercuryLang)
![C++](https://img.shields.io/badge/Made%20with-C++-blue.svg)

<p align="center">
  <img src="./logo.png" alt="MercuryLang Logo" width="200"/>
</p>

---

**MercuryLang** is a lightweight, free, and open-source programming language written in **C++**, inspired by the simplicity of **Lua** and **Python**. It provides clean syntax, dynamic typing, powerful standard libraries, and a fast interpreter — ideal for beginners and language creators alike.

---

## 🚀 Features

- 🔹 Python-like clean syntax
- 🔹 First-class functions
- 🔹 Built-in math & list support
- 🔹 Dynamic variables and control flow
- 🔹 Interactive REPL + `.mer` file runner
- 🔹 C++ API to embed or customize MercuryLang

---

## 📦 Download

👉 [Download MercuryLang (.exe for Windows)](https://github.com/dinhsonhai132/MercuryLang-download/raw/refs/heads/main/MercuryLang-init.exe)

✅ Or you can go to this website https://dinhsonhai132.github.io/main.html to see more useful information 

---

## ⚙️ Getting Started

### Prerequisites

- C++ Compiler (MSVC / GCC / Clang)
- [CMake](https://cmake.org/) 3.12+

### Running Mercury

```bash
mer           # Launch REPL
mer main.mer  # Run file
```

---

## 🧠 Syntax Guide

### 📤 Output
```mer
import "IO" # standard IO library

print("hello world") # output: hello world
```

### 🔢 Variables
```mer
import "IO"

let x = 10
print(x)
```

### 📋 Lists
```mer
import "IO"

let fruits = ["apple", "banana", "water"]
print(fruits[0])
```

### 🧠 Lambda
```mer
import "IO"

let f(x) = x * 2
print(f(3))
```

### 🧠 Functions
```mer
import "IO"

func add(x, y) do
    return x + y
end

print(add(2, 3))
```

### 🔀 While loop
```mer
import "IO"

let x = 0
while x < 100 do
    print(x)
    x += 1
end
```

### 🔀 For loop
```
import "IO"

for i in range(0, 1000) do
    print(i)
end
```

### 🔀 Do loop
```
import "IO"

let x = 0
loop
    print(x)
    x += 1

    if x > 100 then
        break
    end
end
```

### 🔀 If-elif-else statement
```
import "IO"

let a = 1

if a == 1 then
    print("a = 1")
end

elif a == 2 then
    print("a = 2")
end

else
    print("other value")
end
```

### 📜 Other syntax
MercuryLang also supports many other syntax features such as `break`, `return`, `continue`, `and`, `or`, `not`, `is`, `include`, `import`, `do`, `end`, `if`, `elif`, `else`, `while`, `for`, `loop`, and more.

---

## 🧬 Embedding MercuryLang in C++

```cpp
#include <Mercury.h>

int main() {
    let_S   = "gan";
    PRINT_S = "in";
    WHILE_S = "lap";
    IF_S    = "neu";
    THEN_S  = "thi";
    END_S   = "ketthuc";

    LANGUAGE = "MercuryLangTiengViet";
    AUTHOR   = "Dinh Son Hai";

    prompt();
}
```

---

## 📕 library installation

If ```Python``` has ```pip```, so ```MercuryLang``` has ```mpi```

---

### 🔍 What is ```mpi```?
 - **`mpi`** (Mercury Package Installer) is the official tool for installing external libraries in **MercuryLang** — just like `pip` in Python.

- Unlike Python or Lua which use centralized **package markets**,  
  **MercuryLang uses GitHub** as the main source for libraries.

---

### 🚀 How to install a library?

Installing a library with `mpi` is simple. Just type:

```bash
mpi --install https://github.com/author/repo
```

Example:
```bash
mpi --install https://github.com/dinhsonhai132/math
```

When done just import it:
```
import "math"
```

> Replace `author/repo` with the actual GitHub repository of the library you want to install.

---

### 📁 Required Files in a Library Repo

To be recognized as a valid MercuryLang library, the repository **must contain**:

#### 1. `main.mer`
- This is the **entry point** of the library.
- If it’s missing or named incorrectly, `mpi` will reject the repo.

#### 2. `mpi.json`
- A metadata file that describes the library.
- Example format:

```json
{
  "name": "your-library-name",
  "version": "1.0.0",
  "description": "A short description of your library.",
  "author": "YourName"
}
```
