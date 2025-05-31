SOURCE_FILE = C:\MercuryLang\Program\mer.cpp
TARGET = C:\MercuryLang\bin\mer.exe

BYTECODE_SOURCE_FILE = C:\MercuryLang\Program\merc.cpp
BYTECODE_TARGET = C:\MercuryLang\bin\merc.exe

SOURCE_3_FILE = C:\MercuryLang\Program\mer3.cpp
BYTECODE_3_TARGET = C:\MercuryLang\bin\mer3.exe

SOURCE_FILE_TEST_TARGET = C:\MercuryLang\bin\mert.exe
SOURCE_FILE_TEST_TARGET2 = C:\MercuryLang\bin\test.exe


STATIC = --static
CXX = g++
all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(STATIC) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(STATIC) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(STATIC) -DMERCURY_LANG3 $(SOURCE_3_FILE) -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c ".\install.bat"
clean:
	rm -f $(TARGET)
