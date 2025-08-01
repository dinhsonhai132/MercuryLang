### Lambda Functions in MercuryLang

Lambda functions, also called **anonymous functions**, let you create short, one-line functions **without using `func ... end`**. They are useful for simple calculations or passing functions as values.

---

### 1. Defining a Lambda Function

Use the syntax:

```
let <name>(<parameters>) = <expression>
```

Example:

```
let f(x) = x + 1
print(f(5))
```

Output:

```
6
```

Here, `f` is a lambda function that takes one argument `x` and returns `x + 1`.

---

### 2. Multiple Arguments

You can define lambda functions with multiple parameters:

```
let add(a, b) = a + b
print(add(3, 4))
```

Output:

```
7
```

---

### 3. Using Lambdas Inline

Lambdas can also be used inline, stored in variables, or passed to other functions:

```
let square(x) = x * x
let numbers = [1, 2, 3]

for n in numbers do
    print(square(n))
end
```

Output:

```
1
4
9
```

---

Lambda functions are a **concise** way to define small behaviors without writing full `func` definitions.
