# MercuryLang Vector Library (Vector)

**Library Name:** `vector`  
**Last Update:** 7/9/2025  
**Created by:** dinhsonhai132  
**License:** Free to modify and use

The **MercuryLang Vector Library** provides functions to manipulate **dynamic lists (vectors)** in MercuryLang.  
It includes operations like extending, inserting, finding min/max values, and more.

---

## 1. Functions

### 1.1 `extend(list, new_items)`

Extends a list by appending all elements from another list.

```mercury
import "vector"

a = [1, 2, 3]
extend(a, [4, 5, 6])
print(a) # [1, 2, 3, 4, 5, 6]
```

---

### 1.2 `insert(list, index, items)`

Inserts elements into a list **starting at the given index**.  
If `items` is a list, all elements are inserted in order.

```mercury
a = [1, 4, 5]
insert(a, 2, [2, 3])
print(a) # [1, 4, 2, 3, 5]
```

---

### 1.3 `max(list)`

Returns the **largest element** in the list.

```mercury
a = [1, 4, 2, 3, 5]
print(max(a)) # 5
```

---

### 1.4 `min(list)`

Returns the **smallest element** in the list.

```mercury
a = [1, 4, 2, 3, 5]
print(min(a)) # 1
```

---

## 2. Example Usage

```mercury
import "IO"
import "vector"

a = [1, 2, 3]
extend(a, [1 ,2, 3])
print(a) # [1, 2, 3, 1, 2, 3]

a = [1, 4, 5]
insert(a, 2, [2, 3])
print(a) # [1, 4, 2, 3, 5]

print(max(a)) # 5
print(min(a)) # 1
```

---

## 3. Summary

The `vector` library is perfect for:

* Extending and inserting elements in lists  
* Quickly finding min and max values  
* Handling dynamic arrays in MercuryLang

It makes list manipulation **simpler and more powerful** for developers.
