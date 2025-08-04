### MercuryLang Commands Overview

MercuryLang provides **two main commands**:

1. `mer` – runs MercuryLang programs
2. `merc` – works similarly to `mer`, but often used for debugging and compiler output

However, there are **more options** you can use.

---

### Checking the Current Version

To check the version of MercuryLang installed, type:

```
mer -v
```

You can also use `merc` the same way:

```
merc -v
```

Both commands will display the current MercuryLang version.

---

### Viewing Bytecode

MercuryLang compiles `.mer` files into **bytecode**, stored in:

```
__mercache__/<your_program>.merc-250.merc
```

This raw bytecode file is **hard to read** directly.

If you want to see a **human-readable bytecode representation**, run:

```
mer -m <your_program>.mer
```

This will compile your program and show a simplified bytecode output in the console, helping you understand how MercuryLang interprets your code.

---

### Other

If you want to see **all available commands and options**, type:

```
mer -h
```

It will display helpful information about using MercuryLang.
