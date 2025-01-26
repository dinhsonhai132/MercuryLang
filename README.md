### ⚠️ Warning: before you read 
```README.md```
### , this langluage is still not in finish, that's mean it doesn't support strong library, datatype, function,... all just for test before the offical version out, if you want to try the full version of the langluage please wait until the version 1.0.1a (beta) is out, Thanks you all for trying my langluage


--------
# 🟠 Mercury Programming Language

Welcome to ```MercuryLang``` version ```1.1.1```, a simple programming language inspired by Python. Mercury is designed for clean, readable, and powerful code, making it ideal for developers of all levels.

## 🌟 Features

- **Python-like Syntax**: Intuitive and easy-to-read code.
- **Datatype worring**: You don't need worry to much about datatype
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

FOR i IN 1 TO 10 DO PRINT i END;

```

### While loop

```mercury
LET INT x = 0;
WHILE x < 10 DO ++x; PRINT x END;
```

## 🤝 Contributing

We welcome contributions! Submit issues, suggest features, or contribute code:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a description of your changes.

## 🔎 Contact

For questions or suggestions, reach out:

- GitHub: [Mercury Language Discussions](https://github.com/dinhsonhai132/Mercury-Langluage/discussions/1)
>
(You guys can write suggestion and i will hear you all 😁)
