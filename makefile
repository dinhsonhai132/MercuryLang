SOURCE_FILE = ./Program/main.cpp

TARGET = ./bin/mer.exe
BYTECODE_TARGET = ./bin/merc.exe
BYTECODE_3_TARGET = ./bin/mer3.exe

STATIC = --static
CXX = g++

PATH_1 = "./Mercury/builtin.cpp"
PATH_2 = "./Mercury/ceval.cpp"

memory_leak_test = -fsanitize=address -g

all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(STATIC)  $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(STATIC) -DMERCURY_LANG3 -DSYSTEM_TEST $(SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(STATIC) -DMERCURY_LANG3 $(SOURCE_FILE)  -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c ".\install.bat"
clean:
	rm -f $(TARGET)
