# MercuryLang Standard IO Library

**Library Name:** io
**Last Update:** 7/9/2025
**Created by:** dinhsonhai132
**License:** Free to modify and use

The `io` library in MercuryLang provides essential input/output functionality for printing values to the console and reading input from the user. This library is designed to make debugging, output formatting, and simple input operations easier.

---

## 1. Functions

### 1.1 `print(value)`

The `print` function displays the provided value in a **human-readable** format and automatically adds a new line at the end.

**Supported behavior:**

* **List values (type 5):**

  * Printed in square brackets `[...]`.
  * Strings inside lists are printed with quotes.
  * Multiple items are separated by a comma and space.
  * Handles empty lists and single-element lists.

* **Boolean values (type 2):**

  * Prints `true` if the value is `1`.
  * Prints `false` if the value is `0`.

* **Other types:**

  * Prints the raw value followed by a newline.

**Example:**

```mercury
print("Hello World")    # Output: Hello World
print([1, 2, 3])        # Output: [1, 2, 3]
print(["a", "b"])      # Output: ["a", "b"]
print(true)             # Output: true
```

---

### 1.2 `puts(value)`

The `puts` function prints the provided value **without automatically adding formatting or a newline**.

**Usage:**

* Use `puts` when you need low-level output control.
* Useful for building strings or custom formatting in loops.

**Example:**

```mercury
puts("Loading...")
puts(123)
```

---

### 1.3 `input()`

The `input` function waits for the user to **enter a line of text** and returns it as a string.

**Behavior:**

* Reads a single line of input from the console.
* Returns the user input without extra formatting.

**Example:**

```mercury
let name = input()
print("Hello, ")
print(name)
```

If the user types `Alice`, the output will be:

```
Hello,
Alice
```

---

## 2. Summary

* Use **`print`** for formatted, easy-to-read output.
* Use **`puts`** for raw, low-level output without additional formatting.
* Use **`input`** to capture user input as a string.
* The `io` library is a fundamental part of MercuryLang and can be imported in any project for output and input purposes.
