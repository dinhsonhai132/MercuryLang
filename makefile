SOURCE_FILE = C:\MercuryLang\main\main1.cpp
TARGET = C:\MercuryLang\bin\mer.exe
BYTECODE_SOURCE_FILE = C:\MercuryLang\main\main2.cpp
BYTECODE_TARGET = C:\MercuryLang\bin\merc.exe
SOURCE_3_FILE = C:\MercuryLang\main\main3.cpp
BYTECODE_3_TARGET = C:\MercuryLang\bin\mer3.exe
REALM_SOURCE = C:\MercuryLang\main\main4.cpp
REALM_SOURCE_TARGET = C:\MercuryLang\bin\mercury.exe

CXX = g++
all:
	@cmd /c "echo|set /p=mer.exe building... & $(CXX) $(SOURCE_FILE) -o $(TARGET) > nul 2>&1 && echo  [Passed] || echo  [Build failed]"
	@cmd /c "echo|set /p=merc.exe building... & $(CXX) $(BYTECODE_SOURCE_FILE) -o $(BYTECODE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mer3.exe building... & $(CXX) $(SOURCE_3_FILE) -o $(BYTECODE_3_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
	@cmd /c "echo|set /p=mercury.exe building... & $(CXX) $(REALM_SOURCE) -o $(REALM_SOURCE_TARGET) > nul 2>&1 && echo [Passed] || echo [Build failed]"
clean:
	rm -f $(TARGET)
