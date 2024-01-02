CXX = g++
CXXFLAGS = -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC_FILES = Main.cpp Algorithm.cpp Map.cpp

# Output executable
OUTPUT = a.out

all:
	$(CXX) -o $(OUTPUT) $(SRC_FILES) $(CXXFLAGS) $(SFML_LIBS)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
