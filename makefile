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

	@echo Testing syntax before run...

	@ $(CXX) $(STATIC) -DSYSTEM_TEST $(SOURCE_FILE) -o $(SOURCE_FILE_TEST_TARGET)	

	@echo Almost done!

	@ $(CXX) $(STATIC) -DMERCURY_EVAL_THIS_PROGRAM $(SOURCE_FILE) -o $(SOURCE_FILE_TEST_TARGET2)


	@test C:\MercuryLang\Test\math\add.mer
	@test C:\MercuryLang\Test\math\sub.mer
	@test C:\MercuryLang\Test\math\mul.mer
	@test C:\MercuryLang\Test\math\div.mer
	@test C:\MercuryLang\Test\math\mod.mer
	@test C:\MercuryLang\Test\state\func.mer
	@test C:\MercuryLang\Test\state\while.mer
	@test C:\MercuryLang\Test\state\let.mer
	@test C:\MercuryLang\Test\state\builtin.mer
	@test C:\MercuryLang\Test\state\list.mer
	@test C:\MercuryLang\Test\state\condition.mer
	@test C:\MercuryLang\Test\state\print.mer
	@test C:\MercuryLang\Test\state\assign.mer

	@echo Done!
clean:
	rm -f $(TARGET)
