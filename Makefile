CXX = g++
CXXFLAGS = -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC_FILES = MacMan.cpp Algorithm.cpp Map.cpp Sprite.cpp Ghost.cpp Mac.cpp Animation.cpp State.cpp

# Output executable
OUTPUT = pac

all:
	$(CXX) -o $(OUTPUT) $(SRC_FILES) $(CXXFLAGS) $(SFML_LIBS)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
