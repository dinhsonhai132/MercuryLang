# MercuryLang Dynamic Library: Extending Lists and Strings

**Feature:** `dll_load`  
**Last Update:** 7/9/2025  
**Created by:** dinhsonhai132  
**License:** Free to modify and use

MercuryLang allows calling **C++ functions** from external dynamic libraries (`.dll` on Windows or `.so` on Linux) using the `dll_load` function.  
This feature makes it easy to extend MercuryLang with **high-performance native code**.

---

## 1. Overview

`dll_load` lets MercuryLang call native functions:

```mercury
dll_load("<path_to_dll>", "<function_name>", [arg1, arg2, ...])
```

- `<path_to_dll>`: Path to the compiled DLL or shared library.  
- `<function_name>`: Name of the exported C++ function.  
- `[arg1, arg2, ...]`: Arguments passed as a Mercury list.  

**Return Value:**  
The return value of the DLL function (as a Mercury `table*` object).

---

## 2. Example: Extending Lists or Strings

### 2.1 C++ Implementation

The C++ code below demonstrates how to create a dynamic library that **extends lists or strings**:

```cpp
#include <Mercury.h>  // Include Mercury API

START_DLL  // Required macro for Mercury DLL

// Exported function must return table* and accept table* args[]
DLL_EXPORT table* extend(table* args[]) {
    table *item1 = args[0];
    table *item2 = args[1];

    if (item1->is_list && item2->is_list) {
        item1->list_v->args.insert(item1->list_v->args.end(),
                                   item2->list_v->args.begin(),
                                   item2->list_v->args.end());
        item1->list_v->size += item2->list_v->size;
        return item1;
    }

    else if (item1->is_str && item2->is_str) {
        item1->f_str_v->buff.insert(item1->f_str_v->buff.end(),
                                    item2->f_str_v->buff.begin(),
                                    item2->f_str_v->buff.end());
        item1->f_str_v->size += item2->f_str_v->size;
        return item1;
    }

    else {
        item1->cval += item2->cval;
        item1->value += item2->value;
        return item1;
    }
}

END_DLL  // Required macro
```

---

### 2.2 MercuryLang Side

Compile the C++ file into a `.dll` (Windows), then call it from MercuryLang:

```mercury
func extend(item1, item2) do
    return dll_load("init.dll", "extend", [item1, item2])
end

extend([1, 2, 3], [4, 5, 6])  # => [1, 2, 3, 4, 5, 6]
extend("Hello, ", "World!")   # => "Hello, World!"
```

---

## 3. Summary

With `dll_load`, you can:

* Call native C++ functions from MercuryLang  
* Extend the language with high-performance libraries  
* Manipulate lists, strings, or numbers using custom DLL functions

This allows **easy integration** of MercuryLang with **system-level or optimized code**.
