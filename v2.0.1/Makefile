SOURCE_FILE = ./usr/shell.cpp
BYTECODE_SOURCE_FILE = ./usr/exec.cpp

TARGET = ./usr/bin/mer
BYTECODE_TARGET = ./usr/bin/merc
CXX = g++

all:
	$(CXX) $(SOURCE_FILE) -o $(TARGET)
	$(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET)

clean:
	rm $(TARGET) $(BYTECODE_TARGET)