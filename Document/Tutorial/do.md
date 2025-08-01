### Do Loops in MercuryLang

`do` loops in MercuryLang are used to **execute a block of code repeatedly** until you choose to stop it with control flow like `break`. Unlike `while` loops, a `do` loop always **executes at least once**.

---

### 1. Basic Syntax

```
do
    <statements>
end
```

Example:

```
let x = 0
do
    print(x)
    x += 1
    if x > 3 then
        break
    end
end
```

Output:

```
0
1
2
3
```

---

### 2. Using `break` and `continue`

Like `while` loops, `do` loops support `break` to exit early and `continue` to skip the current iteration:

```
let x = 0
do
    x += 1
    if x == 2 then
        continue
    end
    print(x)
    if x == 5 then
        break
    end
end
```

Output:

```
1
3
4
5
```

(The value 2 is skipped.)

---

### 3. Infinite Loops

If you don’t include a `break` statement, a `do` loop will run indefinitely:

```
do
    print("Running...")
end
```

Use `Ctrl + C` in the MercuryLang shell to stop the program.

---

`do` loops are useful for continuous tasks, games, or programs where you need to ensure the block runs at least once.
