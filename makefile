SOURCE_FILE = ./Program/mer.cpp
TARGET = ./bin/mer.exe
BYTECODE_SOURCE_FILE = ./Program/merc.cpp
BYTECODE_TARGET = ./bin/merc.exe
SOURCE_3_FILE = ./Program/mer3.cpp
BYTECODE_3_TARGET = ./bin/mer3.exe

STATIC = --static
CXX = g++
all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(STATIC) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(STATIC) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(STATIC) -DMERCURY_LANG3 $(SOURCE_3_FILE) -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c ".\install.bat"
clean:
	rm -f $(TARGET)
