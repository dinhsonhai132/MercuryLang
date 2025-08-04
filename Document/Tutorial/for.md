### For Loops in MercuryLang

`for` loops in MercuryLang are used to **iterate over sequences of values**, making it simple to repeat tasks a specific number of times.

---

### 1. Basic Syntax

```
for <variable> in <list> do
    <statements>
end
```

Example:

```
for x in [1, 2, 3, 4] do
    print(x)
end
```

Output:

```
1
2
3
4
```

---

### 2. Iterating Over a `range`

The `range(a, b)` function quickly generates a list of numbers from `a` to `b - 1` (if `b > a`). This makes `for` loops especially useful for counting or repeated operations:

```
for i in range(1, 5) do
    print(i)
end
```

Output:

```
1
2
3
4
```

---

### 3. For Loop with Conditional Logic

You can combine `for` loops with `if` conditions to filter values:

```
for i in range(1, 6) do
    if i % 2 == 0 then
        print(sub(to_str(i), " is even"))
    end
end
```

Output:

```
2 is even
4 is even
```

---

`for` loops in MercuryLang are simple yet powerful for iterating over lists, ranges, and sequences.
