### List Expressions in MercuryLang

In MercuryLang, **list expressions** allow you to store multiple values in a single variable. A **list** is a collection of elements, which can be numbers, strings, or even a mix of both.

**Examples of lists:**

```
[1, 2, 3]
["a", 1]
```

Lists are enclosed in square brackets `[` `]` and elements are separated by commas.

---

### Using Lists for math

You can create a list and store it in a variable:

```
> let numbers = [1, 2, 3];
> let mixed = ["a", 1];
```

### Using `+` and `*` with Lists in MercuryLang

MercuryLang supports two special operators for working with lists:

1. **`+` (Concatenation)** – Joins two lists together  
2. **`*` (Repetition)** – Repeats a list multiple times

---

#### 1. `+` Operator (Concatenation)

The `+` operator concatenates two lists and returns a new list:

```mercury
a = [1, 2, 3]
b = [4, 5, 6]

print(a + b)
# Output: [1, 2, 3, 4, 5, 6]
```

#### 2. `*` Operator (Repetition)

```
a = [1, 2, 3]

print(a * 2)
# Output: [1, 2, 3, 1, 2, 3]
```

---

MercuryLang currently provides **two main functions** for list manipulation:

1. `push(list, element)` – Add an element to the **end** of the list
2. `pop(list)` – Remove and return the **last** element from the list

---

### Accessing and Modifying Elements by Index

Lists are **zero-indexed**, meaning the first element is at index `0`. Use square brackets to access or modify an element:

```
> let a = [10, 20, 30];
> print(a[0]);
10
> print(a[1]);
20

> a[1] = 2;
> print(a);
[10, 2, 30]
```

If you try to access an index that doesn’t exist, MercuryLang will return an error.

---

### Example: Using `push` and `pop`

```
> let my_list = [1, 2];
> push(my_list, 3);
> print(my_list);
[1, 2, 3]

> let last_item = pop(my_list);
> print(last_item);
3
> print(my_list);
[1, 2]
```

Step by step:

1. Start with `[1, 2]`
2. `push(my_list, 3)` → `[1, 2, 3]`
3. `pop(my_list)` removes `3` → `[1, 2]`

---

### Generating Lists with `range`

MercuryLang also supports generating lists using the `range(a, b)` function. It creates a list starting from `a` up to `b - 1`, **if `b > a`**.

**Example:**

```
> let r = range(1, 5);
> print(r);
[1, 2, 3, 4]
```

`range(a, b)` is a quick way to create sequences of numbers.

---

Currently, MercuryLang lists are simple but effective for:

* Storing sequences of data
* Accessing elements with indexes
* Modifying elements in place
* Adding/removing elements with `push` and `pop`
* **Generating sequences with `range(a, b)`**
