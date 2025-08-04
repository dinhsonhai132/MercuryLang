# MercuryLang Standard Random Library

**Library Name:** random
**Author:** dinhsonhai132
**License:** Free to modify and use

The `random` library in MercuryLang provides functions for generating **pseudo-random numbers** and selecting random elements from lists.

---

## 1. Functions

### 1.1 `random()`

Returns a pseudo-random floating-point number between **0** and **1**.

```mercury
func random() do
    return __rand()
end
```

**Example:**

```mercury
import "Random2" # name of library

print(random()) # Output: 0.73491 (varies)
```

---

### 1.2 `randbelow(n)`

Returns a random **integer** between `0` and `n-1`.

```mercury
func randbelow(n) do
    if n < 0 then
        return 0
    end
    return to_int(__rand() * n)
end
```

* Returns `0` if `n` is negative.

**Example:**

```mercury
print(randbelow(10)) # Output: random int 0-9
```

---

### 1.3 `randint(a, b)`

Returns a random integer between **a** and **b**, inclusive.

```mercury
func randint(a, b) do
    if a > b then
        return 0
    end
    return a + randbelow(b - a + 1)
end
```

* Returns `0` if `a > b`.

**Example:**

```mercury
print(randint(1, 6)) # Output: random int 1-6
```

---

### 1.4 `choice(list)`

Selects and returns a **random element** from the given list.

```mercury
let choice(l) = l[randint(0, size(l) - 1)]
```

**Example:**

```mercury
print(choice(["apple", "banana", "cherry"])) # Output: random "fruit"
```

---

## 2. Summary

The `random` library provides:

* `random()` for random floats `[0, 1)`
* `randbelow(n)` for random integers below `n`
* `randint(a, b)` for random integers in a range
* `choice(list)` for selecting random elements

This library is essential for **games**, **simulations**, and **randomized algorithms** in MercuryLang.
