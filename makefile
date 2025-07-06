SOURCE_FILE = ./Program/main.cpp

TARGET = ./bin/mercury.exe
BYTECODE_TARGET = ./bin/merc.exe

STATIC = --static
CXX = g++

PATH_1 = "./Mercury/builtin.cpp"
PATH_2 = "./Mercury/ceval.cpp"

memory_leak_test = -fsanitize=address -g

all:
	@cmd /c "echo|set /p=mercury.exe building... & $(CXX) $(STATIC)  $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c ".\install.bat"
clean:
	rm -f $(TARGET)
