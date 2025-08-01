# MercuryLang Math Library

**Library Name:** math
**Last Update:** 7/9/2025
**Created by:** dinhsonhai132
**License:** Free to modify and use

The `math` library in MercuryLang provides a collection of **constants and functions** for performing common mathematical operations. This library is intended for both basic and moderately advanced calculations.

---

## 1. Global Constants

The library defines several **global constants** for mathematical operations:

```mercury
let pi = 3.1415926535897932384626433832795
let e = 2.7182818284590452353602874713527
let tau = 6.283185307179586476925286766559
let gr = 1.6180339887498948482045868343656
```

**Meaning:**

* `pi`  – The mathematical constant π
* `e`   – Euler's number
* `tau` – 2π
* `gr`  – The golden ratio

---

## 2. Functions

### 2.1 Angle Conversion

```mercury
let to_radian(degree) = degree * pi / 180
```

Converts degrees to radians.

---

### 2.2 Factorial

```mercury
func factorial(value) do
    let result = 1
    let i = 1
    while i <= value do
        result *= i
        i += 1
    end
    return result
end
```

Calculates the factorial of a positive integer.

**Example:**

```mercury
print(factorial(5)) # Output: 120
```

---

### 2.3 Square Root

```mercury
func sqrt(value) do
    let x = value
    let guess = x / 2
    let i = 0
    while i < 10 do
        guess = (guess + x / guess) / 2
        i += 1
    end
    return guess
end
```

Computes the square root using the Newton-Raphson method with 10 iterations.

---

### 2.4 Power

```mercury
func power(value, times) do
    let i = 1
    let result = value
    while i < times do
        result *= value
        i += 1
    end
    return result
end
```

Calculates `value ^ times`.

Shorthand helpers:

```mercury
let square(x) = x * x
let cube(x) = square(x) * x
```

---

### 2.5 Trigonometric Functions

#### Sine

```mercury
func sin(degree) do
    # Taylor series approximation for sin(x)
end
```

#### Cosine

```mercury
func cos(degree) do
    # Taylor series approximation for cos(x)
end
```

* Inputs are in **degrees**, internally converted to radians.
* Calculated using **Taylor series** up to 10 iterations.

---

### 2.6 Expression Evaluation (Simple)

```mercury
func eval(expression) do
    # Supports only + and - operations for integer expressions
end
```

Evaluates a string expression containing digits, `+` and `-`.

**Example:**

```mercury
print(eval("10+20-5")) # Output: 25
```

---

## 3. Summary

The `math` library provides:

* **Common constants**: `pi`, `e`, `tau`, `gr`
* **Basic math functions**: `factorial`, `sqrt`, `power`, `square`, `cube`
* **Trigonometry**: `sin`, `cos`
* **Simple expression evaluation** with `eval`

This library is designed to cover everyday computational needs and basic numeric utilities for MercuryLang projects.
