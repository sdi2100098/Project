# Define directories for source, object, include files, and output files
SRC_DIR = source_files
OBJ_DIR = obj
INC_DIR = Include
OUT_DIR = DatasetsReadable
TEST_DIR = test

# Target to build the executable
build: $(OBJ_DIR)

# Target to build and run all tests in one file
test_all: $(OBJ_DIR)

# New target to run tests with Valgrind (without rebuilding the entire program)
valgrind_tests: test_all
		@echo "Running tests with Valgrind..."
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./run_all_tests

# New target to build the main program and run it with Valgrind
valgrind_build: build
		@echo "Running the build with Valgrind..."
		valgrind --leak-check=full --track-origins=yes --verbose ./build $(ARGS)

