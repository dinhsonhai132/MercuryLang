### Creating and Running a MercuryLang Program

To create a program in **MercuryLang**, follow these steps:

1. **Create a file** with the extension `.mer`.
   Example: `main.mer`

2. **Open any text editor** and write your first program:

```
import "IO"

print("hello world")
```

3. **Run the program** in Command Prompt by typing:

```
mer main.mer
```

**Example session:**

```
Microsoft Windows [Version 10.0.26100.4652]
(c) Microsoft Corporation. All rights reserved.

C:\Users\admin>mer main.mer
hello world
C:\Users\admin>
```

> **Note:** The file **must** end with `.mer` — otherwise, MercuryLang will not recognize or execute it.

---

### Writing a More Complex Program

MercuryLang supports variables and loops, so you can create more dynamic programs:

```
import "IO"

let x = 0
while x < 100 do
    x += 1
    print(x)
end
```

This program will count from `1` to `100` and print each number on a new line.
