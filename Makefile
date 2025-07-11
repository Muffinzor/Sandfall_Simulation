CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# SFML configuration (assumes pkg-config is installed and configured for SFML)
SFML_FLAGS = $(shell pkg-config --cflags --libs sfml-graphics sfml-window sfml-system)

# Sources and target
SOURCES = main.cpp Grid.cpp Utility.cpp
TARGET = sand_simulator

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES) $(SFML_FLAGS)

# Clean build files
clean:
	rm -f $(TARGET)
