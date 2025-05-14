SOURCE_FILE = C:\MercuryLang\Program\mer.cpp
TARGET = C:\MercuryLang\bin\mer.exe

BYTECODE_SOURCE_FILE = C:\MercuryLang\Program\merc.cpp
BYTECODE_TARGET = C:\MercuryLang\bin\merc.exe

SOURCE_3_FILE = C:\MercuryLang\Program\mer3.cpp
BYTECODE_3_TARGET = C:\MercuryLang\bin\mer3.exe

SOURCE_FILE_TEST = C:\MercuryLang\Program\mert.cpp
SOURCE_FILE_TEST_TARGET = C:\MercuryLang\bin\mert.exe


STATIC = --static
CXX = g++
all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(STATIC) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(STATIC) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(STATIC) -D__mer3 $(SOURCE_3_FILE) -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mert.exe building... & $(CXX) $(STATIC) -DSYSTEM_TEST $(SOURCE_FILE_TEST) -o $(SOURCE_FILE_TEST_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
clean:
	rm -f $(TARGET)
