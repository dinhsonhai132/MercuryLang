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
 - You can download by go to this website **[MercuryLang-website](https://dinhsonhai132.github.io/main.html)**

## 🚀 Execution

- After installation, you can launch the interactive prompt by typing ```mer``` or ```merc```, ```mer3```
- If you want to run file, create a file name ```.mer``` and type ```mer main.mer``` or ```merc main.mer```, ```mer3 main.mer```

## 🔧 Language Syntax

### Print function
```rust
!write("hello")
```

### Variable
```python
# use LET keyword
LET x = 2
LET y = 3
```

### List expression
```python
# List syntax is [ e1, e2, e3, ... ] list element only suport int, float type
[1, 2, 3, 5]
```

### List Statement
```python 
# store list into variable using keyword 'LIST'
LIST a = [1, 2, 3]
!write(a[0])                    # you can extract the element from the list
LET size = !size(a)             # use !size() function to get the size of the list
!watch(a)                       # use !watch() to see every elements in the list
!pop(a)                         # use !pop() to pop the last elements from the list
!push(a, 1)                     # use !push() to push the value on top of the list
```

### Global variable
```rust
!write(pi)
!write(euler)
!write(golden_ratio)
!write(tau)
```

### Math
```python
# Merucury support '+', '-', '/', '*', '%'
2 * 2
3 + 3 / 2
1 % 2
```

### Comparison
```python
# support >, <, <=, >=, ==, !=
LET x = 2
LET y = 3
PRINT x > y
```
### Function and function call
```python
FUNC foo() DO
    LET x = 1
    LET y = 2
    PRINT x + y
END

# function call start with `!`
!foo()
```

### If-else statement
```python
IF 1 == 1  THEN
    LET x = 1
    LET y = 1
    PRINT x + y
END

ELSE
    LET x = 1
    LET y = 1
    PRINT x - y
END
```

### Assignment
```python
LET x = 1
x = x + 1
PRINT x
```

### While loop
```python
LET x = 0
WHILE x < 10 DO
    x = x + 1
    PRINT x
END
```

### Example code
```python
# TODO: print all elements of the list

LIST exp = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
LET exp_size = !size(exp)
LET index = 0

WHILE index < exp_size DO
    !write(exp[index])
    index = index + 1
END
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
