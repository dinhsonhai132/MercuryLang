this is README for test
# MercuryLang *version 2.0.1 binary* is out! ✨
## What's in this update? 👀

## 1) New Compiler called Mercury Virtual Machine (MVM) 💻
### What's is MVM? 
* MVM is a compiler that compile low level programing language make for execute Mercury codes 
### What MVM can do? 
* MVM can do a basic codes like what a basic low level programing language can do for example:
```MVM
PROGRAM_START
PUSH_FLOAT 1.000000
PUSH_FLOAT 1.000000
BINARY_ADD
PROGRAM_END
```
* That code is the compiled code of:
``` MercuryLang
1+1
```
### Why use MVM? 
* Using MVM to execute code is faster and easier to manage the code 
* By not straight code from AST to value can not cause a lot of error when new version update or small mistake run code 
## 2) How to install and setup new version?
* First, install the program language, extract all files
* Then, open terminal enter the ```../v2.0.1``` path
* Run ```make``` to make ```mer.exe``` file
* When done, creat a folder named ```Mercury``` in ```C:/```
* Edit evironment path to your ```C:/Mercury``` folder
* When done go to terminal type ```mer --version``` if it show 2.0.1 that means you are done
## 3) How to execute *.mer* file
* When setup is done just type ```mer your_project.mer``` it will execute into ```your_project.merc```, that file is your bytecode

**And that are all the feature that the 2.0.1 MercuryLang has, have fun coding 😆**
