# MercuryLang *version 2.0.1 binary* is out! ✨
## What's in this update? 👀

## 1) New Compiler called Mercury Virtual Machine (MVM) 💻
### What's is MVM? 
* MVM is a compiler that compile low level programing language make for execute Mercury codes 
### What MVM can do? 
* MVM can do a basic codes like what a basic low level programing language can do for example:
```mercury
PROGRAM_START
PUSH_FLOAT 1.000000;
PUSH_FLOAT 1.000000;
BINARY_ADD;
PROGRAM_END
```
* That code is the compiled code of:
``` mercury
1 + 1
```
### Why use MVM? 
* Using MVM to execute code is faster and easier to manage the code 
* By not straight code from AST to value can not cause a lot of error when new version update or small mistake run code 
## 2) How to install and setup new version?
* First, install the program language [using this link](https://github.com/dinhsonhai132/Mercury-Langluage/archive/refs/heads/main.zip) and extract all files to your ```C:\``` 
* Second, open terminal and go to your ```v2.0.1``` MercuryLang file
* Third, run make to make ```mer.exe``` and ```merc.exe``` and ```mer3.exe```
* Finally, edit environment part to your ```C:\MercuryLang-main\v2.0.1\usr\bin```
## 3) How to run file?
* Run ```mer your_file_name.mer``` to creat ```.merc``` file and then run ```merc your_bytecode_file.merc``` or ```merc --run your_bytecode_file``` to run your bytecode file
* Or you can run ```mer3 your_file_name.mer``` to creat ```your_bytecode_file.merc-250.merc``` in your ```__mercache__``` folder
