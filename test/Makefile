CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SOURCE = $(wildcard src/*.cpp)
OBJECT = $(SOURCE:.cpp=.o)

EXEC = shell.exe

all: $(EXEC)

# Build executable
$(EXEC): $(OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT) $(EXEC)
