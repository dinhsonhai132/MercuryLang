### Math Expressions in MercuryLang

Every programming language provides a basic feature: **mathematical expressions**.

In **MercuryLang**, you can calculate any expression, and it will produce the evaluated result. You can use standard operators such as:

* `+` (addition)
* `-` (subtraction)
* `*` (multiplication)
* `/` (division)
* `(` and `)` (grouping)

**Example:**

```
MercuryLang 2.2.1 Copyright (C) 2025-present, dinhsonhai132
> import "IO";
> print(1 + 1); // calculate basic expression and print the output: "1 + 1" -> "2"
2
>
```

As you can see, MercuryLang successfully calculates the math expression `1 + 1` and prints the correct output `2` to the console using the `print` function.

---

### Floating-Point Arithmetic

MercuryLang supports floating-point values in expressions. For example:

```
> print(24.2 * 2 / 100 * (2 / 2.32));
0.417241379310345
```

Here, MercuryLang evaluates the expression with decimal numbers (floats) and produces the accurate floating-point result.

> **Tip:** `0.5` is written with a **dot**, not a comma (`0.5`, not `0,5`).

---

### Floor Division and Modulo

MercuryLang can also handle more advanced math operations:

* **Floor division**: `//` – divides and returns the integer part of the result.
* **Modulo**: `%` – calculates the remainder of the division.

```
> print(17 // 3)
5
> print(17 % 3)
2
```

With these operators, MercuryLang allows you to create both simple and complex mathematical expressions with ease.
