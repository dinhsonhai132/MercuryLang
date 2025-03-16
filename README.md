# 🪐 *Mercury Programming Language*

Welcome to ```MercuryLang``` version ```2.0.1b``` a test version of ```2.0.1```, a simple interpreter by ```C++``` programming language inspired by Python. Mercury is designed for clean, readable, and powerful code, making it ideal for developers of all levels.

## 🌟 Features

- **Python-like Syntax**: Intuitive and easy-to-read code.
- **Datatype warring**: You don't need worry to much about datatyped
- **Custom Functions**: Create flexible functions with ease.
- **Error Handling**: Debug efficiently with clear error messages.
- **Extensive Standard Library**: Tools for data manipulation, file handling, and more.

## 📒 Getting Started

### Prerequisites

Before using Mercury, ensure you have:

- A ```C++``` compiler (Mercury is implemented in ```C++```)
- CMake (to build from source)

### Installation

1. **Download** the MercuryLang [using this link](https://github.com/dinhsonhai132/Mercury-Langluage/archive/refs/heads/main.zip)
2. **Extract** all file to the ```C:\```
3. **Open terminal** and go to ```C:/mercurylang-main/v2.0.1/usr/bin```, run ```make``` to make file, if it say ```Run successfully```  mean you are right
5. **Edit enviroment path** to the ```C:/mercurylang-main/v2.0.1/usr/bin```
   
### Hello, World!
**Make** a ```.mer``` file 
**Open terminal** and go to your ```.mer``` file then **run** ```mer your_file_name.mer```, It will compiled your program into ```.merc``` file
**Run** ```merc your_file_name.merc``` to execute your program, if you want to see the result run ```merc --run your_file_name.merc``` it will execute and print the result to your screen

## 🔧 Language Syntax
**Although it's still a test version of ```v2.0.1``` but it's still have a few feature of ```v1.0.1``` like**
### Variable
```mercury
LET x = 1
LET y = 3
```
### Function call
```mercury
!println("hello world")
```
### Function statment
```mercury
FUNC foo() DO
LET x = 1
LET y = 3
x + y
END

!foo()
```

### Example of bytecode
```mercury
PROGRAM_START
LOAD_GLOBAL a;
LOAD_GLOBAL c;
PROGRAM_END

<address of global a at 0x2AADA2A8>
PUSH_FLOAT 1.000000;
STORE_GLOBAL x;
RETURN

<address of global c at 0x5CBC1FFA>
PUSH_FLOAT 1.000000;
STORE_GLOBAL y;
RETURN
```

**It's a compiled version of**
```mercury
FUNC a() DO
LET x = 1
END
FUNC c() DO
LET y = 1
END
!a()
!b()
```
## 🤝 Contributing

We welcome contributions! Submit issues, suggest features, or contribute code:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

## 🔎 Contact

For questions or suggestions, reach out:

- GitHub: [Mercury Language Discussions](https://github.com/dinhsonhai132/Mercury-Langluage/discussions/1)
- Youtube: https://www.youtube.com/@haidinhson
- Gmail: dinhsonhai440@gmail.com
(You guys can write suggestion and i will hear you all 😁)
made by : Dinh Son Hai
