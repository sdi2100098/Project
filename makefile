# C++ compiler we use
CXX = g++

CXXFLAGS = -Wall -std=c++17 -lstdc++ -O3 -fopenmp -IInclude

# Output filename after compilation 
TARGET = build

# Directory for object files
OBJ_DIR = obj

# Source files (without main.cpp)
SRC = source_files/Read_Data.cpp\
		source_files/Delete_Data.cpp\
		source_files/FindMedoid.cpp \
		source_files/EuclideanDistance.cpp \
		source_files/RandomPermutation.cpp \
		source_files/CreateKNNG.cpp \

# Test file
TEST_SRC = test/Test_All.cpp

# Create object file names for each source file
OBJ = $(SRC:source_files/%.cpp=$(OBJ_DIR)/%.o)

# Main target
all: $(TARGET)

# Build main executable
$(TARGET): source_files/main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) source_files/main.cpp $(OBJ)

# Build object files (without main.cpp)
$(OBJ_DIR)/%.o: source_files/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run main executable
run: $(TARGET)
	./$(TARGET)

# Run the tests (compile and run the tests directly without creating a separate executable)
test: $(TEST_SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) -o test_executable $(TEST_SRC) $(OBJ)
	./test_executable

# Run valgrind for main executable
valgrind_main: $(TARGET)
	@echo "Running the build with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

# Run valgrind for test executable
valgrind_test: test
	@echo "Running tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test_executable

# Clean up object files and executables
clean:
	rm -rf $(TARGET) $(OBJ_DIR) test_executable