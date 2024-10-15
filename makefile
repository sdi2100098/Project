# Define directories for source, object, include files, and output files
SRC_DIR = source_files
OBJ_DIR = obj
INC_DIR = Include
OUT_DIR = DatasetsReadable

# Target to build the executable
build: $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o
	g++ -o build $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o $(OBJ_DIR)/EuclidianDistance.o

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

# Rule to ensure DatasetsReadable directory is created
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Clean rule to remove the object files and the executable
clean:
	rm -rf $(OBJ_DIR) build $(OUT_DIR)
