CXX = g++
CXXFLAGS = -IInclude -std=c++11 -O3  # Point -I to the Include directory
TARGET = file
SRC = source_files/main.cpp   # Add all relevant .cpp files here

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)  # Compile all .cpp files

clean:
	rm -f $(TARGET)
