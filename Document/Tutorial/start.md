### Getting Started with MercuryLang

If you are new here, **MercuryLang** is the perfect choice for you. It features:

* **No complex syntax** – simple and easy to understand.
* **No low-level complexity** like C or C++, so you can focus on building.
* **Powerful capabilities** to help you create many useful applications.

---

### Running MercuryLang

The MercuryLang interpreter is always located at:

```
C:/MercuryLang/bin
```

Currently, it supports **Windows** only. To start the interactive shell, open **Command Prompt** and type:

```
mer
```

Example session:

```
Microsoft Windows [Version 10.0.26100.4652]
(c) Microsoft Corporation. All rights reserved.

C:\Users\admin>mer
MercuryLang 2.2.1 Copyright (C) 2025-present, dinhsonhai132
>
>
>
```

You can exit the shell by pressing **Ctrl + C** or by calling the `exit()` function.

---

### Interactive Shell Mode

In **shell mode**, MercuryLang executes your commands **line by line**:

```
MercuryLang 2.2.1 Copyright (C) 2025-present, dinhsonhai132
> import "IO";
> print("hi")
hi
>
```

---

### Debugging with `merc`

If you want to see **how your commands are processed by the compiler**, MercuryLang provides a debug tool called `merc`. It will show each compilation and execution step:

```
C:\Users\admin>merc
MercuryLang 2.2.1 Copyright (C) 2025-present, dinhsonhai132
> let x = 1;
[compiler.cpp] [MerCompiler_compile_ast_program] [start]
[compiler.cpp] [MerCompiler_compile_ast_program] [pass]
[compiler.cpp] [MerCompiler_compile_ast_literal] [pass]
[compiler.cpp] [MerCompiler_compile_ast_let] [pass]
[compiler.cpp] [MerCompiler_compile_ast_id_expression_statment] [pass]
[ceval.cpp] [MerVM_evaluate_program] [building...]
[ceval.cpp] [__get_label_map] [building...]
[ceval.cpp] [__get_label_map] [pass]
[ceval.cpp] [MerVM_evaluate_program] [pass]
[ceval.cpp] [MerVM_evaluate_statement] [building...]
[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [building...]
[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [pass]
[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [building...]
[ceval.cpp] [pop_stack] [start]
[ceval.cpp] [pop_stack] [pass]
[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [pass]
[ceval.cpp] [MerVM_evaluate_statement] [pass]
>
```
