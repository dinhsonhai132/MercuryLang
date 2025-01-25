# 🟠 Mercury Programming Language

Welcome to ```MercuryLang```, a simple programming language inspired by Python. Mercury is designed for clean, readable, and powerful code, making it ideal for developers of all levels.

## 🌟 Features

- **Python-like Syntax**: Intuitive and easy-to-read code.
- **Dynamic Typing**: Skip worrying about variable types.
- **Custom Functions**: Create flexible functions with ease.
- **Error Handling**: Debug efficiently with clear error messages.
- **Extensive Standard Library**: Tools for data manipulation, file handling, and more.

## 📒 Getting Started

### Prerequisites

Before using Mercury, ensure you have:

- A ```C++``` compiler (Mercury is implemented in ```C++```)
- CMake (to build from source)

### Installation

1. Download the MercuryLang [using this link](https://github.com/dinhsonhai132/Mercury-Langluage)
2. Extract all file

### Hello, World!

Make a ```.txt``` file and write your first Mercury program:

```mercury
PRINT "HELLO WORLD!";
```

Run the program:
Open ```shell.exe``` file and write the name of your ```.txt``` file or you can open ```shell.exe``` file and type ```run``` to run code in command line

## 🔧 Language Syntax

### Variables

```mercury
LET INT x = 2;
LET FLOAT y = 3.2;
LET STRING z = "hello";
PRINT x + y;
```

### Functions

Define functions with parameters:

```mercury
FUNC add(&x, &y) DO PRINT &x + &y;
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
IF x > 0 THEN PRINT "x is greater than zero" ELSE PRINT "x is not greater than zero";
```

### Lists

Create and manipulate lists:

```mercury
LIST a = [1, 2, 3, 4];
PRINT @a -> 1; /* first element start with 1 */
```

### Math

```mercury
LET INT x = 0;
PRINT ++x /* plus plus or minus minus will update the value */;
PRINT --x;
PRINT x * 2 / 3 + 1;
```

### For loop

```mercury
/* for loop in list */

LIST a = [4, 3, 2, 5, 3];
FOR i IN @a DO PRINT i;

/* for loop in range */

FOR i IN 1 TO 10 DO PRINT i;

```

### While loop

```mercury
LET INT x = 0;
WHILE x < 10 DO ++x; PRINT x;
```

## 🤝 Contributing

We welcome contributions! Submit issues, suggest features, or contribute code:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

## 🔎 Contact

For questions or suggestions, reach out:

- GitHub: [Mercury Language Discussions](https://github.com/dinhsonhai132/Mercury-Langluage/discussions/1)
