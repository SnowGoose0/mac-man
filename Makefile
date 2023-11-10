CXX = g++
CXXFLAGS = -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC_FILES = MacMan.cpp Animation.cpp Map.cpp Sprite.cpp

# Output executable
OUTPUT = pac

all:
	$(CXX) -o $(OUTPUT) $(SRC_FILES) $(CXXFLAGS) $(SFML_LIBS)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)