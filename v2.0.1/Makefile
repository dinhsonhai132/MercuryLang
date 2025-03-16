SOURCE_FILE = ./usr/shell.cpp
BYTECODE_SOURCE_FILE = ./usr/exec.cpp

TARGET = ./usr/bin/mer
BYTECODE_TARGET = ./usr/bin/merc
CXX = g++

all:
	@echo "Building... (mer.exe)"
	@$(CXX) $(SOURCE_FILE) -o $(TARGET) > /dev/null 2>&1 || { echo "Build failed!"; exit 0; }

	@echo "Building... (merc.exe)"
	@$(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > /dev/null 2>&1 || { echo "Build failed!"; exit 0; }

	@echo "Run successfully!"

clean:
	@rm -f $(TARGET) $(BYTECODE_TARGET) > /dev/null 2>&1
