CXX = g++
CXXFLAGS = -std=c++11
SFML_INCLUDE = -I/path/to/sfml/include
SFML_LIBS = -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files directory
SRC_DIR = ./src

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Output executable
OUTPUT = MacMan

all: $(OUTPUT)

$(OUTPUT): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -o $@ $^ $(SFML_LIBS)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
