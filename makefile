# Define directories for source, object, and include files
SRC_DIR = source_files
OBJ_DIR = obj
INC_DIR = Include

# Target to build the executable
build: $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o
	g++ -o build $(OBJ_DIR)/main.o $(OBJ_DIR)/Read_Vector.o

# Rule for main.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o -I$(INC_DIR)

# Rule for Read_Vector.o
$(OBJ_DIR)/Read_Vector.o: $(SRC_DIR)/Read_Vector.cpp $(INC_DIR)/Library.hpp
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC_DIR)/Read_Vector.cpp -o $(OBJ_DIR)/Read_Vector.o -I$(INC_DIR)

# Clean rule to remove the object files and the executable
clean:
	rm -rf $(OBJ_DIR) build
