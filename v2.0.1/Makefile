SOURCE_FILE = ./usr/main2.cpp
BYTECODE_SOURCE_FILE = ./usr/main1.cpp
MERCURY3_SOURCE_FILE = ./usr/main3.cpp
TEST_FILE = ./usr/main4.cpp

TARGET = ./usr/bin/mer.exe
BYTECODE_TARGET = ./usr/bin/merc.exe
MERCURY3 = ./usr/bin/mer3.exe
TEST_TARGET = ./usr/bin/test.exe

CXX = g++

all:
	@echo mer.exe building...
	@$(CXX) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]

	@echo merc.exe building...
	@$(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]

	@echo mer3.exe building...
	@$(CXX) $(MERCURY3_SOURCE_FILE) -o $(MERCURY3) > nul 2>&1 && echo [Passed] || echo [Build failed]

	@echo test.exe building...
	@$(CXX) $(TEST_FILE) -o $(TEST_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]
clean:
	@del /F /Q $(TARGET) $(BYTECODE_TARGET) $(MERCURY3) 2> nul
	@echo Cleaned!
