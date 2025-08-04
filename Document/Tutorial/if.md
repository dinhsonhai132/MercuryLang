### If Statements in MercuryLang

MercuryLang provides **if statements** to make decisions in your programs. They are used to execute code only when a specific **condition** is true.

---

### 1. Comparison and Logical Rules

To create conditions, you can use **comparison operators**:

* `==` : Equal to
* `!=` : Not equal to
* `>`  : Greater than
* `<`  : Less than
* `>=` : Greater than or equal to
* `<=` : Less than or equal to

And **logical operators** to combine conditions:

* `and` : True if **both** conditions are true
* `or`  : True if **at least one** condition is true
* `not` : Inverts the boolean value (True → False, False → True)

Boolean values in MercuryLang are:

* `true`
* `false`

**Example:**

```
> let x = 10
> let y = 5
> print(x > 5 and y < 10)
true
```

---

### 2. Basic `if` Statement Syntax

```
if <condition> then
    <statements>
end
```

Example:

```
let x = 5
if x > 0 then
    print("Positive")
end
```

---

### 3. `if / elif / else` Syntax

To handle multiple conditions, use `elif` and `else`:

```
if <a> then
    <b>
end

elif <c> then
    <d>
end

else
    <e>
end
```

Example:

```
let score = 65

if score >= 90 then
    print("Excellent")
end

elif score >= 50 then
    print("Pass")
end

else
    print("Fail")
end
```

Output:

```
Pass
```

---

With these rules, you can create **dynamic and flexible** decision-making in your MercuryLang programs.
