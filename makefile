# MAIN SOURCE FILE
SOURCE_FILE = ./Program/main.cpp

# TARGETS
TARGET = ./bin/mer.exe
TEST = ./bin/merc.exe
GC = ./bin/mgc.exe
MPI_SOURCE = ./Mpi/main.cpp
MPI_TARGET = ./bin/mpi.exe

STATIC = --static
CXX = g++

all:
	@cmd /c "echo Building..."
	@ g++ $(STATIC) $(SOURCE_FILE) -o $(TARGET)
	@ g++ -DSYSTEM_TEST $(SOURCE_FILE) -o $(TEST)
	@ g++ $(MPI_SOURCE) -o $(MPI_TARGET)
	@ @echo off
	@ copy C:\MercuryLang\Program\Mercury.h C:\msys64\ucrt64\include
	@ cmd /c "echo Done!"
clean:
	@if exist $(TARGET) del /f /q $(TARGET)
	@if exist $(TEST) del /f /q $(TEST)
	@if exist $(MPI_TARGET) del /f /q $(MPI_TARGET)
