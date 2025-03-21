> [!WARNING]
> **Before you read this, this language is still in working, that's mean it's not a offical version yet, all for test. If you want to try a completed version, wait until version 1.0.1a is out. Thanks for paying attention to my programming language.**

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
  
-------------------------------------------------------------------------------------------------------------------------------------------
1. **Download** the MercuryLang [using this link](https://github.com/dinhsonhai132/Mercury-Langluage/archive/refs/heads/main.zip)
2. **Extract** all file and go to ```v1.5.0``` or you can go to ```v2.0.1``` to see new version tutorial
3. **Run** ```shell.cpp``` into ```shell.exe```
4. **Open** ```shell.exe``` and run in **prompt** mode
5. If you want to run file **creat** a ```.mer``` file
6. **Open** ```shell.exe``` and type your ```.mer``` file, it will execute your program
## 🔧 Language Syntax
### Variable
```mercury
 LET INT x = 2;
 LET FLOAT y = 3.2;
 LET STRING z = "hello";
 PRINT x + y;
```
### Functions
 Define functions with parameters:
 ```mercury
FUNC add(&x, &y) DO PRINT &x + &y END;
 !add(1, 2);
```
 ### Compair
 Mercury include a large compair operators
 ```mercury
 PRINT 1 == 1; /* value will be 1(true) or 0(false) */
 LET INT x = 2;
 LET INT y = 5;
 PRINT x <= 2;
 PRINT x > 4;
 PRINT x != y;
 ```
### Control Flow
 Mercury includes standard control flow statements:
 ```mercury
 LET INT x = 0;
 IF x > 0 THEN PRINT "x is greater than zero" END ELSE PRINT "x is not greater than zero" END;
 ++x;
 IF x != 1 THEN PRINT "x is not 1" END ELIF x == 1 THEN PRINT "x is 1" END;
 ```
### For loop
```mercury
/* for loop in list */
 
 LIST a = [4, 3, 2, 5, 3];
 FOR i IN @a DO PRINT i;
 
 /* for loop in range */
 
 FOR i IN 1 TO 10 DO PRINT i END;
 ```
### Lists
 Create and manipulate lists:
 ```mercury
 LIST a = [1, 2, 3, 4];
 PRINT @a -> 1; /* first element start with 1 */
 ```
### While loop
 ```mercury
 LET INT x = 0;
 WHILE x < 10 DO ++x; PRINT x END;
 ```
 ### Code block
 ```mercury
 /*code block store multiline */
 ... DO (code_block) END;
 ```

## 🤝 Contributing

We welcome contributions! Submit issues, suggest features, or contribute code:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

## 🔎 Contact

For questions or suggestions, reach out:

- GitHub: **[Mercury Language Discussions](https://github.com/dinhsonhai132/Mercury-Langluage/discussions/1)**
- Youtube: **https://www.youtube.com/@mercurylang-official**
- Gmail: **dinhsonhai440@gmail.com**

*(You guys can write suggestion and i will hear you all 😁)*

**Author: dinhsonhai132**
