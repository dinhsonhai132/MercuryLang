### Variables in MercuryLang

Variables are used to **store data** that can be accessed and modified later. MercuryLang supports simple and clear syntax for declaring and updating variables.

---

### 1. Declaring Variables

Use the `let` keyword to declare a variable and assign a value:

```
let a = 1
let name = "MercuryLang"
```

This creates variables `a` and `name`.

You can also **reassign** variables without `let` once they exist:

```
x = 2
```

---

### 2. Updating Variables

MercuryLang supports **arithmetic assignment operators** to update variable values easily:

* `+=` : Add and assign
* `-=` : Subtract and assign
* `*=` : Multiply and assign
* `/=` : Divide and assign

Example:

```
let x = 2
x += 1  # x = 2 + 1
print(x)
3
```

---

### 3. Using Variables in Expressions

Variables can be used in **mathematical and string expressions**:

```
let a = 10
let b = 5
print(a + b)    # 15

let msg = "Hello"
print(sub(msg, " World"))  # "Hello World"
```

---

Variables are a core feature of MercuryLang, enabling you to store numbers, strings, and lists, and perform calculations dynamically.
