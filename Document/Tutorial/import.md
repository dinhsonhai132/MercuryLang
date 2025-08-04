# MercuryLang Module System

MercuryLang provides a simple **module system** with `include` and `import` statements, allowing you to organize and reuse your code efficiently.

---

## 1. include "file"

The `include` statement **loads a file from the exact path** you specify.
This is similar to `#include` in C/C++ and is useful for directly including local files.

**Example:**

```mercury
include "C:/Projects/utils.mer"
include "./Modules/math.mer"
```

Behavior:

* The file is loaded and executed in the **current context**.
* If the file does not exist at the given path, an error is raised.
* The file name must include the **extension** (e.g., `.mer`).

---

## 2. import "file"

The `import` statement is designed for **modular libraries**.
It automatically looks for the file in the following locations:

1. `C:/MercuryLang/Libs/<file>`
2. `C:/MercuryLang/Libs/__libs__/<file>`

### 2.1 Importing a File

You can import any file (with or without an extension):

```mercury
import "math"         # will look for 'math' file in C:/MercuryLang/Libs/
import "graphics.mer" # will look for 'graphics.mer' file in C:/MercuryLang/Libs/
```

Search behavior:

1. Try `C:/MercuryLang/Libs/math` (with or without extension)
2. Try `C:/MercuryLang/Libs/__libs__/math/main.mer`

If the file exists, it will be loaded automatically.

---

### 2.2 Importing a Folder

If the imported name is a **folder**, MercuryLang will attempt to load it as a **module directory**:

```mercury
import "MGL"
```

Folder structure example:

```
C:/MercuryLang/Libs/__libs__/
└── MGL/
    ├── main.mer
    └── readme.md
```

Behavior:

* MercuryLang will automatically look for **file** `MGL` in `C:/MercuryLang/Libs` if not in there MercuryLang will know its a folder and look up in `C:/MercuryLang/Libs/__libs__`
* If its found MercuryLang will check the `C:/MercuryLang/Libs/__libs__/library/mpi.json`
* Then MercuryLang will looks for a **main.mer** file in the folder and executes it.

---

## 3. Summary

* **`include`**: Load a file from an **exact path**.
* **`import`**: Load a file or folder from the **MercuryLang library directories**.
* Supports multiple file types: `.mer`, `.cpp`, `.py`, or no extension.
* Importing a folder automatically looks for `main.mer` inside it.

By combining `import` and `include`, you can build **modular, reusable code** in MercuryLang while keeping your project organized.