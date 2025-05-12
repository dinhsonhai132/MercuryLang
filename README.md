> [!IMPORTANT]  
> Version 1.0.1-alpha is out now

# 🪐 *Mercury Programming Language*

**Welcome to ```MercuryLang``` — a free and open-source lightweight interpreter written in **C++**, inspired by the simplicity of Python. ```MercuryLang``` is designed to offer clean, readable, and expressive syntax, making it an ideal choice for developers of all experience levels.**

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
 - You can download MercuryLang by download this program: **[MercuryLang-init](https://github.com/dinhsonhai132/MercuryLang-download/raw/refs/heads/main/MercuryLang-init.exe)**

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
# TODO: print the number from 1 to 100 that divisible by 2

LET max = 100
LET number = 0

WHILE number <= max DO
    IF number % 2 == 0 THEN
        PRINT number
    END
    number = number + 1
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

**Version: 1.0.1-alpha**
