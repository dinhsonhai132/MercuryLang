this is README for test
# MercuryLang *version 2.0.1 binary* is out! ✨
## What's in this update? 👀

## 1) New Compiler called Mercury Virtual Machine (MVM) 💻
### What's is MVM? 
* MVM is a compiler that compile low level programing language make for execute Mercury codes 
### What MVM can do? 
* MVM can do a basic codes like what a basic low level programing language can do for example:
```mercury
PROGRAM_START
LOAD_GLOBAL a;
LOAD_GLOBAL c;
PROGRAM_END

<address of global a at 0x2AADA2A8>
PUSH_FLOAT 1.000000;
STORE_GLOBAL x;
RETURN

<address of global c at 0x5CBC1FFA>
PUSH_FLOAT 1.000000;
STORE_GLOBAL y;
RETURN
```
* That code is the compiled code of:
``` mercury
FUNC a() DO
LET x = 1
END
FUNC c() DO
LET y = 1
END
!a()
!b()
```
### Why use MVM? 
* Using MVM to execute code is faster and easier to manage the code 
* By not straight code from AST to value can not cause a lot of error when new version update or small mistake run code 
## 2) How to install and setup new version?
* First, install the program language, extract all files to your ```C:\```
* Second, open terminal and go to your ```v2.0.1``` MercuryLang file
* Third, run make to make ```mer.exe``` 
* Finally, edit environment part to your ```C:\MercuryLang-main\v2.0.1```
* Now you can open terminal and type ```mer --version``` if it show *2.0.1* mean you are right

**And that are all the feature that the 2.0.1 MercuryLang has, have fun coding 😆**
