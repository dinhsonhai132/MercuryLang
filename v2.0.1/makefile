SOURCE_FILE = C:\MercuryLang\v2.0.1\main\main1.cpp
TARGET = C:\MercuryLang\v2.0.1\bin\mer.exe

BYTECODE_SOURCE_FILE = C:\MercuryLang\v2.0.1\main\main2.cpp
BYTECODE_TARGET = C:\MercuryLang\v2.0.1\bin\merc.exe

SOURCE_3_FILE = C:\MercuryLang\v2.0.1\main\main3.cpp
BYTECODE_3_TARGET = C:\MercuryLang\v2.0.1\bin\mer3.exe

CXX = g++

all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(SOURCE_3_FILE) -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
clean:
	rm -f $(TARGET)