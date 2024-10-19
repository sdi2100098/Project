# Define directories for source, object, include files, and output files
SRC_DIR = source_files
OBJ_DIR = obj
INC_DIR = Include
OUT_DIR = DatasetsReadable
TEST_DIR = test

# Target to build the executable
build: $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/GreedySearch.o
	g++ -o build $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/GreedySearch.o

# Target to build the tests
test: $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/Test_RandomPermutation.o
	g++ -o run_tests $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/Test_RandomPermutation.o -I$(INC_DIR) -I$(TEST_DIR)

# Rule for Test_RandomPermutation.o (Test file)
$(OBJ_DIR)/Test_RandomPermutation.o: $(TEST_DIR)/Test_RandomPermutation.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(TEST_DIR)/Test_RandomPermutation.cpp -o $(OBJ_DIR)/Test_RandomPermutation.o -I$(INC_DIR) -I$(TEST_DIR)

# Rule for main.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o -I$(INC_DIR)

# Rule for Read_Vector.o
$(OBJ_DIR)/Read_Vector.o: $(SRC_DIR)/Read_Vector.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Read_Vector.cpp -o $(OBJ_DIR)/Read_Vector.o -I$(INC_DIR)

# Rule for EuclidianDistance.o
$(OBJ_DIR)/EuclidianDistance.o: $(SRC_DIR)/EuclidianDistance.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/EuclidianDistance.cpp -o $(OBJ_DIR)/EuclidianDistance.o -I$(INC_DIR)

# Rule for GetRandomNumber.o
$(OBJ_DIR)/GetRandomNumber.o: $(SRC_DIR)/GetRandomNumber.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/GetRandomNumber.cpp -o $(OBJ_DIR)/GetRandomNumber.o -I$(INC_DIR)

# Rule for RandomPermutation.o
$(OBJ_DIR)/RandomPermutation.o: $(SRC_DIR)/RandomPermutation.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/RandomPermutation.cpp -o $(OBJ_DIR)/RandomPermutation.o -I$(INC_DIR)

# Rule for GreedySearch.o
$(OBJ_DIR)/GreedySearch.o: $(SRC_DIR)/GreedySearch.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/GreedySearch.cpp -o $(OBJ_DIR)/GreedySearch.o -I$(INC_DIR)

# Rule to ensure DatasetsReadable directory is created
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Clean rule to remove the object files and the executable
clean:
	rm -rf $(OBJ_DIR) build $(OUT_DIR) run_tests
