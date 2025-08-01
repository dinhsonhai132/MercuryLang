### String Expressions in MercuryLang

In MercuryLang, **string expressions** are used for text instead of math operations.

A **`string`** can contain:

* **Single characters**: `!`, `@`, `?`, etc.
* **Words**: `hello`, `MercuryLang`
* **Sentences**: `Hello, world!`

Strings are **enclosed in double quotes** (`" "`) so the MercuryLang compiler can recognize them as string literals. If you forget the quotes, the compiler will not know what it is and will report an error.

```
> print("Hello, world!");
Hello, world!
>
```

---

### Escaping Characters

MercuryLang treats the **second** `"` as the **end of the string**. If you want to include a double quote **inside** the string, escape it with a backslash `\`:

```
> print("\"this is a string\"")
"this is a string"
>
```

The backslash allows you to store any character, including a `"`, inside a string.

---

### String Manipulation

Strings in MercuryLang can be manipulated just like math expressions. The `sub` function is used to **concatenate (join)** multiple strings together:

```
> print(sub("hello", "world"));
"hello world"
>
```

The `sub` function provides a simple way to join strings.

---

### Converting Other Types to Strings

You can convert other types (like numbers) to strings using the `to_str` function:

```
> print(to_str(123)); # convert number into string
123.0000000
> print(sub(to_str(1), ".000000"));
1.0000000.000000
```

Here, `to_str` turns a number into a string, which can then be combined with other strings using functions like `sub`.
