```diff
- [WARNING] This programming language is still under active development and is not stable. Using it may cause unexpected behavior, memory leaks, or other critical issues. Many features are incomplete or experimental. It is strongly advised not to use this language in production or for important projects until development is fully completed and thoroughly validated.
```

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

## 🔨 Build from source

**1.** Navigate to the `MercuryLang-main` folder.

**2.** Open **Command Prompt**.

**3.** Run `make` to build from source, and `mer`, `merc`, `mpi` will be in `MercuryLang-main/Bin/`

**4.** **Rename** `MercuryLang-main` into `MercuryLang` and then move it to `C:/`

**5.** **Edit** environment path to `C:/MercuryLang/Bin/`

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

## 🧠 Syntax Guide and Help

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

### 📋 String
```mer
import "IO"

let a = "hello, "
let b = "world"
print(a + b)

```

### 📋 Lists
```mer
import "IO"

let fruits = [["apple, "orange", "pineapple"], "banana", "water"]
fruit *= 2
print(fruits[0][1])

frutis[0][2] = "watermelon"

let other_food = ["fish", "egg"]
print(fruits + other_food)
```

### 🧠 Lambda
```mer
import "IO"

let f(x) = [1, 2, 3, 4, x]
print(f(3)[0])
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

### 🧠 Call `C++` Functions from `MercuryLang`

`MercuryLang` supports calling **C++ functions** from dynamic libraries (`.dll` on Windows) via the `dll_load` function.
```mercury
dll_load("<path_to_dll>", "<function_name>", [arg1, arg2, ...])
```

- `<path_to_dll>`: Path to your compiled DLL or shared library.
- `<function_name>`: Name of the exported C++ function.
- `[arg1, arg2, ...]`: Arguments passed to the C++ function (as a list).

---

### 🛠 Example: Extending Lists or Strings

#### 1️⃣ C++ Implementation

```cpp
#include <Mercury.h>  // Include Mercury API

START_DLL  // Required macro for Mercury DLL

// Exported function must return table* and accept table* args[]
DLL_EXPORT table* extend(table* args[]) {
    table *item1 = args[0];
    table *item2 = args[1];

    if (item1->is_list && item2->is_list) {
        item1->list_v->args.insert(item1->list_v->args.end(),
                                   item2->list_v->args.begin(),
                                   item2->list_v->args.end());
        item1->list_v->size += item2->list_v->size;
        return item1;
    }

    else if (item1->is_str && item2->is_str) {
        item1->f_str_v->buff.insert(item1->f_str_v->buff.end(),
                                    item2->f_str_v->buff.begin(),
                                    item2->f_str_v->buff.end());
        item1->f_str_v->size += item2->f_str_v->size;
        return item1;
    }

    else {
        item1->cval += item2->cval;
        item1->value += item2->value;
        return item1;
    }
}

END_DLL  // Required macro
```

#### 2️⃣ MercuryLang Side

Compile the C++ file into a `.dll` (Windows), then call it from Mercury:

```mercury
func extend(item1, item2) do
    return dll_load("init.dll", "extend", [item1, item2])
end

extend([1, 2, 3], [4, 5, 6])  # => [1, 2, 3, 4, 5, 6]
extend("Hello, ", "World!")   # => "Hello, World!"
```

---

### 📜 Other syntax
MercuryLang also supports many other syntax features such as `break`, `return`, `continue`, `and`, `or`, `not`, `is`, `include`, `import`, `do`, `end`, `if`, `elif`, `else`, `while`, `for`, `loop`, and more.

### 🎮 Game
- MercuryLang has a library for **graphic** and **game** (```MGL```)
- This code here is a example for a simple jumping game using ```MGL```
- If you want to use the library **graphic** and **game** download `SDL3.dll` and then move it into `..\Bin`
```cpp
import "MGL" # import Mercury Game Library

screen_width = 500
screen_height = 500

screen_init(screen_width, screen_height)

cube_width = 50
cube_height = 50

cube_x = 0
cube_y = screen_height - cube_height

cube_vel = 5

cube_color = [255, 255, 255]

while true do
    screen_fill(0, 0, 0)

    screen_draw(cube_x, cube_y, cube_width, cube_height, cube_color[0], cube_color[1], cube_color[2])

    let key = get_key_char(key_pressed())

    if same(key, "a") then
        cube_x -= cube_vel
    end

    if same(key, "d") then
        cube_x += cube_vel
    end

    if cube_x >= screen_width - cube_width then
        cube_x = screen_width - cube_width
    end

    if cube_x <= 0 then
        cube_x = 0
    end

    screen_flip()
end

screen_quit()
```

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

---

**Made** by **dinhsonhai132**
