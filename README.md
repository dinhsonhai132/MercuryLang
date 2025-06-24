# 🪐 Mercury Programming Language

![GitHub Stars](https://img.shields.io/github/stars/dinhsonhai132/MercuryLang?style=social)
![GitHub Forks](https://img.shields.io/github/forks/dinhsonhai132/MercuryLang?style=social)
![Repo Size](https://img.shields.io/github/repo-size/dinhsonhai132/MercuryLang)
![Issues](https://img.shields.io/github/issues/dinhsonhai132/MercuryLang)
![License](https://img.shields.io/github/license/dinhsonhai132/MercuryLang)
![C++](https://img.shields.io/badge/Made%20with-C++-blue.svg)

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

---

## ⚙️ Getting Started

### Prerequisites

- C++ Compiler (MSVC / GCC / Clang)
- [CMake](https://cmake.org/) 3.12+

### Running Mercury

```bash
mer           # Launch REPL
mer file.mer
```

You can also use `merc` or `mer3` aliases.

---

## 🧠 Syntax Guide

### 📤 Output
```mer
print("hello world")
```

### 🔢 Variables
```mer
LET  x = 10
x += 1
```

### 📋 Lists
```mer
LET fruits = ["apple", "banana"]
print(fruits[0])
```

### 🧮 Math & Logic
```mer
IMPORT "math"

LET x = pi
cos(x) + sin(x)

LET a = 2
LET b = 3
print(a < b AND b != 0)
```

### 🧠 Functions
```mer
FUCN add(x, y) DO
    print(x + y)
END

add(2, 3)
```

### 🔀 Control Flow
```mer
IF 1 == 1 THEN
    print("true")
END

ELSE
    print("false")
END

WHILE x < 10 DO
    x += 1
    CONTINUE
END

FOR i IN range(0, 5) DO
    print(i)
END

LOOP
    if x == 10 THEN BREAK END
    x += 1
END
```

---

## 🧬 Embedding MercuryLang in C++

```cpp
#include <Mercury.h>

int main() {
    LET_S   = "gan";
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
