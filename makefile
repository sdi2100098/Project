# Define directories for source, object, include files, and output files
SRC_DIR = source_files
OBJ_DIR = obj
INC_DIR = Include
OUT_DIR = DatasetsReadable
TEST_DIR = test

# Target to build the executable
build: $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/GreedySearch.o $(OBJ_DIR)/Robust_Prune.o $(OBJ_DIR)/Delete_Graph.o $(OBJ_DIR)/Argument_Min_Distance.o $(OBJ_DIR)/Set_Difference.o $(OBJ_DIR)/Medoid.o $(OBJ_DIR)/MultiThread.o
	g++ -pthread -o build $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/GreedySearch.o $(OBJ_DIR)/Robust_Prune.o $(OBJ_DIR)/Delete_Graph.o $(OBJ_DIR)/Argument_Min_Distance.o $(OBJ_DIR)/Set_Difference.o $(OBJ_DIR)/Medoid.o $(OBJ_DIR)/MultiThread.o

# Target to build and run all tests in one file
test_all: $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/Set_Difference.o $(OBJ_DIR)/Test_All.o
	g++ -o run_all_tests $(OBJ_DIR)/RandomPermutation.o $(OBJ_DIR)/EuclidianDistance.o $(OBJ_DIR)/GetRandomNumber.o $(OBJ_DIR)/Set_Difference.o $(OBJ_DIR)/Test_All.o -I$(INC_DIR) -I$(TEST_DIR) -lm
	./run_all_tests

# Rule for Test_All.o (Combined test file)
$(OBJ_DIR)/Test_All.o: $(TEST_DIR)/Test_All.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(TEST_DIR)/Test_All.cpp -o $(OBJ_DIR)/Test_All.o -I$(INC_DIR) -I$(TEST_DIR)

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
	g++ -c $(SRC_DIR)/EuclidianDistance.cpp -o $(OBJ_DIR)/EuclidianDistance.o -I$(INC_DIR) -lm

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

# Rule for Robust_Prune.o
$(OBJ_DIR)/Robust_Prune.o: $(SRC_DIR)/Robust_Prune.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Robust_Prune.cpp -o $(OBJ_DIR)/Robust_Prune.o -I$(INC_DIR)

# Rule for Delete_Graph.o
$(OBJ_DIR)/Delete_Graph.o: $(SRC_DIR)/Delete_Graph.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Delete_Graph.cpp -o $(OBJ_DIR)/Delete_Graph.o -I$(INC_DIR)

# Rule for Argument_Min_Distance.o
$(OBJ_DIR)/Argument_Min_Distance.o: $(SRC_DIR)/Argument_Min_Distance.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Argument_Min_Distance.cpp -o $(OBJ_DIR)/Argument_Min_Distance.o -I$(INC_DIR)

# Rule for Set_Difference.o
$(OBJ_DIR)/Set_Difference.o: $(SRC_DIR)/Set_Difference.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Set_Difference.cpp -o $(OBJ_DIR)/Set_Difference.o -I$(INC_DIR)

# Rule for Medoid.o
$(OBJ_DIR)/Medoid.o: $(SRC_DIR)/Medoid.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Medoid.cpp -o $(OBJ_DIR)/Medoid.o -I$(INC_DIR)

# Rule for MultiThread.o
$(OBJ_DIR)/MultiThread.o: $(SRC_DIR)/MultiThread.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/MultiThread.cpp -o $(OBJ_DIR)/MultiThread.o -I$(INC_DIR)


# Rule to ensure DatasetsReadable directory is created
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Clean rule to remove the object files and the executable
clean:
	rm -rf $(OBJ_DIR) build $(OUT_DIR) run_tests