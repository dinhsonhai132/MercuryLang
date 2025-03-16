SOURCE_FILE = ./usr/shell.cpp
BYTECODE_SOURCE_FILE = ./usr/exec.cpp

TARGET = ./usr/bin/mer
BYTECODE_TARGET = ./usr/bin/merc
CXX = g++

all:
	@printf "mer.exe building... "
	@$(CXX) $(SOURCE_FILE) -o $(TARGET) > /dev/null 2>&1 && printf "\033[1;32mPassed!\033[0m\n" || { printf "\033[1;31mBuild failed!\033[0m\n"; exit 0; }

	@printf "merc.exe building... "
	@$(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > /dev/null 2>&1 && printf "\033[1;32mPassed!\033[0m\n" || { printf "\033[1;31mBuild failed!\033[0m\n"; exit 0; }

clean:
	@rm -f $(TARGET) $(BYTECODE_TARGET) > /dev/null 2>&1
	@printf "\033[1;32mCleaned!\033[0m\n"
