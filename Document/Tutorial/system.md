# MercuryLang System Library

MercuryLang allows you to perform **low-level** operations similar to `C/C++` for working directly with **files**, **directories**, and **system commands**.

```mercury
import "sys" # Import sys standard library
```

---

## **File Operations**

### **Create a file**

Create a new file:

```mercury
create_file("your_file.txt")
```

### **Write to a file**

Overwrite content in a file:

```mercury
write_file("your_file.txt", "this is a txt file")
```

### **Read file content**

Read the content of a file:

```mercury
print(read_file("your_file.txt"))
```

### **Append to a file**

Append content to the end of a file:

```mercury
append_file("your_file.txt", "\nadd more content")
```

### **Copy a file**

Copy a file to a new location:

```mercury
copy_file("your_file.txt", "copy_file.txt")
```

### **Move a file**

Move a file to a different path:

```mercury
move_file("copy_file.txt", "moved_file.txt")
```

### **Rename a file**

Rename a file:

```mercury
rename_file("moved_file.txt", "renamed_file.txt")
```

### **Delete a file**

Delete a file:

```mercury
delete_file("renamed_file.txt")
```

### **Check if a file exists**

Check whether a file exists:

```mercury
if file_exists("your_file.txt") then
    print("File exists!")
end
```

### **Get file size**

Get the file size in bytes:

```mercury
print(file_size("your_file.txt"))
```

---

## **Directory Operations**

### **Create a directory**

```mercury
create_dir("my_folder")
```

### **List directory contents**

```mercury
print(list_dir("my_folder"))
```

### **Check path type**

```mercury
print(is_dir("my_folder"))      # true if directory
print(is_file("your_file.txt")) # true if file
```

### **Copy, Move, Rename, Delete a directory**

```mercury
copy_dir("my_folder", "my_folder_copy")
move_dir("my_folder_copy", "new_location")
rename_dir("new_location", "renamed_folder")
delete_dir("renamed_folder")
```

---

## **System Commands**

### **Run a system command**

```mercury
cmd("echo Hello from MercuryLang!")
```

### **Run a file with a command**

```mercury
run_file_with("python", "script.py")
```

---

With these functions, MercuryLang can manage files and directories like `C/C++` while keeping a simple syntax.
