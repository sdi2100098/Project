# C++ compiler we use
CXX = g++

# CXXFLAGS = -Wall -std=c++17 -lstdc++ -O3 -fopenmp -IInclude
CXXFLAGS = -pg -Wall -std=c++17 -lstdc++ -O3 -fopenmp -IInclude

# Output filenames after compilation
TARGET1 = build_Filtered
TARGET2 = build_Stitched
TARGET3 = build_Filtered_Recall
TARGET4 = build_Stitched_Recall

# Directory for object files
OBJ_DIR = obj

# Source files (without Filtered_Vamana_main.cpp && Stitched_Vamana_main.cpp)
SRC = source_files/Read_Data.cpp\
		source_files/Delete_Data.cpp\
		source_files/FindMedoid.cpp \
		source_files/EuclideanDistance.cpp \
		source_files/RandomPermutation.cpp \
		source_files/Set_Difference.cpp\
		source_files/FilteredRobustPrune.cpp\
		source_files/FilteredGreedySearch.cpp\
		source_files/Argument_Min_Distance.cpp\
		source_files/GroundTruth.cpp\
		source_files/Filtered_Vamana.cpp\
		source_files/PreComputeFun.cpp\
		source_files/StitchedVamana.cpp\
		source_files/Vamana.cpp\
		source_files/GreedySearch.cpp\
		source_files/RobustPrune.cpp\
		source_files/Medoid.cpp\
		source_files/Save_Load_Graph_Binary.cpp
		
# Test file
TEST_SRC = test/Test_All.cpp

# Create object file names for each source file
OBJ = $(SRC:source_files/%.cpp=$(OBJ_DIR)/%.o)

# Main target
all: build_filtered build_stitched build_Stitched_Recall build_Filtered_Recall

# Build Filtered_Vamana_main executable
build_filtered: source_files/Filtered_Vamana_main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) source_files/Filtered_Vamana_main.cpp $(OBJ)

# Build Stitched_Vamana_main executable
build_stitched: source_files/Stitched_Vamana_main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) source_files/Stitched_Vamana_main.cpp $(OBJ)

build_Filtered_Recall: source_files/Filtered_Vamana_Recall.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET3) source_files/Filtered_Vamana_Recall.cpp $(OBJ)

build_Stitched_Recall: source_files/Stitched_Vamana_Recall.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET4) source_files/Stitched_Vamana_Recall.cpp $(OBJ)

# Build object files (without main.cpp)
$(OBJ_DIR)/%.o: source_files/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target for PreCompute
precompute: source_files/PreCompute.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o precompute_executable source_files/PreCompute.cpp $(OBJ)

# Run the PreCompute executable
run_precompute: precompute
	./precompute_executable

# Run Filtered_Vamana_main executable
run_filtered: build_filtered
	./$(TARGET1)

# Run Stitched_Vamana_main executable
run_stitched: build_stitched
	./$(TARGET2)

run_filtered_recall: build_Filtered_Recall
	./$(TARGET3)

run_stitched_recall: build_Stitched_Recall
	./$(TARGET4)

# Run the tests (compile and run the tests directly without creating a separate executable)
test: $(TEST_SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) -o test_executable $(TEST_SRC) $(OBJ)
	./test_executable

# Run valgrind for test executable
valgrind_test: test
	@echo "Running tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test_executable

# Clean up object files and executables
clean:
	rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(OBJ_DIR) test_executable precompute_executable
	rm -f Datasets/Small_Set/Graph_Graph_Precompute.bin Datasets/Small_Set/Graph_Query_Precompute.bin Datasets/Small_Set/dummy-groundtruth.bin Datasets/Small_Set/Graph.bin 
	rm -f Datasets/Small_Set/*.txt
	rm -f *.txt gmon.out
