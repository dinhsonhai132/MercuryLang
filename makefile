# MAIN SOURCE FILE
SOURCE_FILE = ./Program/main.cpp

# TARGET
TARGET = ./bin/mer.exe
TEST = ./bin/merc.exe

# MPI SOURCE FILE
MPI_SOURCE = "./Mpi/main.cpp"
MPI_TARGET = "./bin/mpi.exe"

STATIC = --static
CXX = g++

all:
	@cmd /c "echo Building..."
	@ $(CXX) $(STATIC) $(SOURCE_FILE) -o $(TARGET)
	@ $(CXX) $(STATIC) -DSYSTEM_TEST $(SOURCE_FILE) -o $(TEST)
	@ $(CXX) $(STATIC) $(MPI_SOURCE) -o $(MPI_TARGET)
	@ @echo off
	@ copy C:\MercuryLang\Usr\Mercury.h C:\msys64\ucrt64\include
	@cmd /c "echo Done!"
clean:
	rm -f $(TARGET)
