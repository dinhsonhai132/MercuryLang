# MercuryLang Standard Vector Library

**Library Name:** vector
**Author:** dinhsonhai132
**License:** Free to modify and use

The `vector` library provides **list-based vector operations** for MercuryLang. It is designed to simplify working with lists as mathematical or general-purpose vectors.

---

## 1. Functions

### 1.1 `vector(list)`

Validates that the argument is a list (type `5`).

```mercury
func vector(__vector) do
    if type(__vector) != 5 then
        puts("Error! not a list\n")
        return 0
    end
    return __vector
end
```

* Returns the list if it is valid.
* Prints an error and returns `0` if the argument is not a list.

---

### 1.2 `vector_sub(vec1, vec2)`

Performs element-wise **addition** of two vectors of equal size.

```mercury
func vector_sub(vec1, vec2) do
    if size(vec1) != size(vec2) then
        return 0
    end

    let vec3 = []
    let id = 0
    while id < size(vec1) do
        push(vec3, vec1[id] + vec2[id])
        id += 1
    end
    return vec3
end
```

* Returns a new vector of sums.
* Returns `0` if the input vectors are not the same size.

**Note:** Despite the name `vector_sub`, the current implementation performs **addition**.

---

### 1.3 `append(vec1, vec2)`

Appends all elements of `vec2` to `vec1`.

```mercury
func append(vec1, vec2) do
    for val in vec2 do
        push(vec1, val)
    end
    return vec1
end
```

**Example:**

```mercury
print(append([1, 2], [3, 4])) # Output: [1, 2, 3, 4]
```

---

### 1.4 `clear(vec1)`

Removes all elements from the vector.

```mercury
func clear(vec1) do
    vec1 = vector(vec1)
    let i = 0
    let vsize = size(vec1)
    while i < vsize do
        pop(vec1)
        i += 1
    end
    return vec1
end
```

* Returns the now-empty vector.

---

### 1.5 `copy(vec1)`

Creates and returns a **shallow copy** of a vector.

```mercury
func copy(vec1) do
    let temp = []
    for i in vec1 do
        push(temp, i)
    end
    return temp
end
```

---

### 1.6 `reverse(vec1)`

Reverses the elements of the vector **in place**.

```mercury
func reverse(vec1) do
    vec1 = vector(vec1)
    vsize = size(vec1)
    i = 0
    j = vsize - 1
    while i < j do
        tmp = vec1[i]
        vec1[i] = vec1[j]
        vec1[j] = tmp
        i = i + 1
        j = j - 1
    end
end
```

**Example:**

```mercury
let v = [1, 2, 3]
reverse(v)
print(v) # Output: [3, 2, 1]
```

---

## 2. Summary

The `vector` library provides essential operations for handling lists like vectors:

* **Validation** with `vector()`
* **Element-wise addition** with `vector_sub()`
* **Append, clear, copy, and reverse** utilities

This library is useful for implementing simple linear algebra operations or general list manipulations in MercuryLang.
