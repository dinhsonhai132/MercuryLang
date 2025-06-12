# 🪐 *Mercury Programming Language*

**Welcome to ```MercuryLang``` — a small free and open-source lightweight interpreter written in **C++**, inspired by the simplicity of Python. ```MercuryLang``` is designed to offer clean, readable, and expressive syntax, making it an ideal choice for developers of all experience levels.**

## 🌟 Features

- **Python-like Syntax**: Intuitive and easy-to-read code.
- **Custom Functions**: Create flexible functions with ease.
- **Error Handling**: Debug efficiently with clear error messages.
- **Extensive Standard Library**: Tools for data manipulation, file handling, and more.

## 📒 Getting Started

### Prerequisites

Before building or running MercuryLang, ensure you have the following installed:

- **C++ Compiler**
  - [MSVC](https://visualstudio.microsoft.com/)
  - [Clang](https://clang.llvm.org/)
  - [GCC via MSYS2](https://www.msys2.org/)
  - [GCC](https://gcc.gnu.org/) (for Linux/macOS)

- **[CMake](https://cmake.org/)** – Version 3.12 or higher

## ✅ Download
 - You can download by go to this link **[MercuryLang-download](https://github.com/dinhsonhai132/MercuryLang-download/raw/refs/heads/main/MercuryLang-init.exe)**

## 🚀 Execution

- After installation, you can launch the interactive prompt by typing ```mer``` or ```merc```, ```mer3```
- If you want to run file, create a file name ```.mer``` and type ```mer main.mer``` or ```merc main.mer```, ```mer3 main.mer```

## 🔧 Language Syntax

### Print function
```python
print("hello world")
```

### Variable
```python
let x = 1
let y = 2
```

### List expression
```python
let x = ["apple", "pineapple", "orange"]
print(x[1])
x[1] = "watermelon"
```

### Global variable
```python
write(pi)
write(euler)
write(golden_ratio)
write(tau)
```

### Math
```python
# Merucury support '+', '-', '/', '*', '%'
2 * 2
3 + 3 / 2
1 % 2

# Or you can use buitlin function
let x = pi
cos(x)
sin(x)
tan(x)
cot(x)
sqrt(x)
```

### Comparison
```python
# support >, <, <=, >=, ==, !=
let x = 2
let y = 3
print(x < y)
```
### Function and function call
```python
func foo() do
    let x = 1
    let y = 2
    print(x + y)
end

foo()
```

### If-else statement
```python
if 1 is 1 then print("1 == 1") end
else print("1 != 1") end
```

### Assignment
```python
let x = 1
x = x + 1
x += 1
x -= 1
x *= 1
x /= 1
print(x)
```

### While loop
```python
let x = 0
while x < 100 do
    x += 1
    print(x)

    if x == 5 then
        break
    end
end
```

### Do loop
```python
let x = 0

loop
    if x is 5 then break end
    else x += 1; continue end
end
```

### Example code
```python
# This is a simple shell interpreter that tokenizes a mathematical expression.
# It recognizes numbers and basic arithmetic operators (+, -, *, /).
# # The code is written in a hypothetical language Mer, which is similar to Python.

func break_point() do
    while 1 do end
end

let plus = "plus"
let minus = "minus"

let tokens = []

let buffer = "1 + 1"
buffer = split(buffer)

let index = 0

while index < size(buffer) do
    if index < size(buffer) then let current = buffer[index] end

    if same(current, "+") then push(tokens, plus) end
    if same(current, "-") then push(tokens, minus) end

    if isdigit(current) then
        let num_str = ""
        while isdigit(current) do
            if index < size(buffer) then current = buffer[index] end else break end
            if isdigit(current) then sub(num_str, current) end
            if index < size(buffer) then index += 1 end else break end
        end
        push(tokens, num_str)
        continue
    end

    if index < size(buffer) then index += 1 end
end

# evaluate the tokens
let result = 0
let index = 0

while index < size(tokens) do
    if index < size(tokens) then let current = tokens[index] end
    if same(current, plus) then
        let left = tokens[index - 1]
        let right = tokens[index + 1]
        result += to_int(left) + to_int(right)
    end

    if same(current, minus) then
        let left = tokens[index - 1]
        let right = tokens[index + 1]
        result += to_int(left) - to_int(right)
    end

    if index < size(tokens) then index += 1 end
end

puts("Result: ")
puts(result)
```

## 🔋 Advance

If you want to creat your own language using ```Mercury.h``` just follow these step
- Go to ```C:\MercuryLang\...``` and run ```make``` to build
- Creat a ```.cpp``` file and then you can make your own language

**Example:**
```cpp
#include <Mercury.h> // make your own language using library 'Mercury.h'

int main() {
    // you can change the syntax

    LET_S = "gan";
    WHILE_S = "lap";
    PRINT_S = "in";
    DO_S = "lam";
    END_S = "ketthuc";
    IF_S = "neu";
    THEN_S = "thi";
    ELSE_S = "nguoclai";

    // also you can change the language information
    LANGUAGE = "MercuryLangTiengViet";
    AUTHOR = "Dinh son ha";

    prompt();
}
```

## 🤝 Contributing

We welcome contributions! Submit issues, suggest features, or contribute code:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

## 🔎 Contact

For questions or suggestions, reach out:

- GitHub: **[Mercury Language Discussions](https://github.com/dinhsonhai132/Mercury-Langluage/discussions/1)**
- Youtube: **[@haidinhson](https://www.youtube.com/@haidinhson)**
- Gmail: **dinhsonhai440@gmail.com**

*(You guys can write suggestion and i will hear you all 😁)*

**Author: dinhsonhai132**
