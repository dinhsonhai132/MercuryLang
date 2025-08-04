### Functions in MercuryLang

Functions allow you to **organize your code** into reusable blocks. A function can perform a task and can optionally accept arguments (inputs) and return a value.

---

### 1. Defining a Function

Use the `func` keyword followed by the function name and parentheses `()` for parameters. The function body is enclosed with `do ... end`.

**Syntax:**

```
func <name>() do
    <statements>
end
```

**Example:**

```
func foo() do
    print("Hello from foo")
end
```

---

### 2. Calling a Function

After defining a function, call it using its name and parentheses:

```
foo()
```

Output:

```
Hello from foo
```

---

### 3. Functions with Arguments

Functions can accept **arguments** (also called parameters) to make them dynamic:

```
func greet(name) do
    print(sub("Hello, ", name))
end

# Call the function with an argument
greet("MercuryLang")
```

Output:

```
Hello, MercuryLang
```

You can define functions with multiple arguments:

```
func add(a, b) do
    print(a + b)
end

add(2, 3)  # prints 5
```

---

### 4. Return Values

Functions can return a value using the `return` statement:

```
func square(x) do
    return x * x
end

print(square(4))  # 16
```

---

Functions are essential for writing **clean and reusable code** in MercuryLang, allowing you to break complex tasks into smaller, manageable pieces.
