### While Loops in MercuryLang

`while` loops in MercuryLang are used to **repeat a block of code** as long as a given condition is true. This is useful for running tasks continuously until a condition changes.

---

### 1. Basic Syntax

```
while <condition> do
    <statements>
end
```

Example:

```
let x = 0
while x < 5 do
    print(x)
    x += 1
end
```

This will output:

```
0
1
2
3
4
```

---

### 2. Using `break` and `continue`

MercuryLang supports `break` and `continue` inside loops:

* **`break`**: Immediately exits the loop
* **`continue`**: Skips the current iteration and continues with the next one

Example with `break`:

```
let x = 0
while x < 10 do
    if x == 5 then
        break
    end
    print(x)
    x += 1
end
```

Output:

```
0
1
2
3
4
```

Example with `continue`:

```
let x = 0
while x < 5 do
    x += 1
    if x == 3 then
        continue
    end
    print(x)
end
```

Output:

```
1
2
4
5
```

(The value `3` is skipped.)

---

### 3. Combining `while` with Conditions

`while` loops are often used with comparisons and logical operators to control flow:

```
let x = 0
while x < 5 and x != 3 do
    print(x)
    x += 1
end
```

This loop will print 0, 1, 2 and stop when `x == 3` because the condition becomes false.

---

With `while` loops, `break`, and `continue`, you can build flexible and powerful loops in MercuryLang.
