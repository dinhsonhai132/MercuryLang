# 🪐 *Mercury Programming Language*

![GitHub Stars](https://img.shields.io/github/stars/dinhsonhai132/MercuryLang?style=social)
![GitHub forks](https://img.shields.io/github/forks/dinhsonhai132/MercuryLang?style=social)
![GitHub repo size](https://img.shields.io/github/repo-size/dinhsonhai132/MercuryLang)
![GitHub issues](https://img.shields.io/github/issues/dinhsonhai132/MercuryLang)
![GitHub license](https://img.shields.io/github/license/dinhsonhai132/MercuryLang)

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
import "math" # using math standard library

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
print(x < y and y > x)
print(x == 1 or y == 1)
print(not x)
```
### Function and function call
```python
func foo(x, y) do
    print(x + y)
end

foo(1, 2)
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

### For loop
```python
for i in range(0, 100) do
    if i % 2 == 0 then print(i) end
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
loop
    puts("expr> ")
    buff = input()
    
    plus = "plus"
    minus = "minus"
    
    stack = []
    buff = to_list(buff)
    id = 0
    number = "" 
    
    while id < size(buff) do
        cur = buff[id]
    
        if isdigit(cur) then
            sub(number, cur)
        end
        
        else
            if size(number) > 0 then
                push(stack, number)
                number = ""
            end
    
            if same(cur, "+") then
                push(stack, plus)
            end
            if same(cur, "-") then
                push(stack, minus)
            end
        end
    
        id += 1
    end
    
    if size(number) > 0 then
        push(stack, number)
    end
    
    result = 0
    num = 0
    tok_idx = 0
    op = "plus"
    
    while tok_idx < size(stack) do
        cur = stack[tok_idx]
    
        if isdigit(cur) then
            num = to_int(cur)
    
            if same(op, plus) then
                result += num
            end
            
            if same(op, minus) then
                result -= num
            end
        end
        
        if same(cur, plus) then
            op = plus
        end
        
        if same(cur, minus) then
            op = minus
        end
    
        tok_idx += 1
    end
    
    print(result)
end
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
