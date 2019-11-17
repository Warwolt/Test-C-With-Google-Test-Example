# Define directories
OBJ_DIR = obj
TEST_DIR = ../sw/test
FAKE_DIR = $(TEST_DIR)/fakes
SRC_DIR = ../sw/src
INC_DIR = ../sw/inc

# Libraries
LIB_DIR = ../lib
FFF_INC_DIR = $(LIB_DIR)/fakefunctionframework
GTEST_DIR = $(LIB_DIR)/googletest
GTEST_LIBS = -L$(GTEST_DIR) -lgtest_main -lgtest -pthread

# Outputs
PROD_LIB = $(OBJ_DIR)/prod.a

# Get source files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %.c,%.o, $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC)))
OBJ := $(filter $(OBJ)/main.o, $(OBJ))
FAKE_SRC = $(wildcard $(FAKE_DIR)/*.c)
FAKE_OBJ = $(patsubst %.c,%.o, $(patsubst $(FAKE_DIR)/%, $(OBJ_DIR)/%, $(FAKE_SRC)))
TEST_SRC = $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJ = $(patsubst %.cc,%.o, $(patsubst $(TEST_DIR)/%, $(OBJ_DIR)/%, $(TEST_SRC)))

# Compile flags
C_FLAGS = -Wall -Werror
CC_FLAGS = -std=c++11
INC = -I$(INC_DIR) -I$(FAKE_DIR) -I$(FFF_INC_DIR)
TEST_INC = $(INC) -I$(GTEST_DIR)/include

.PHONY: clean

all:
	@echo "Usage: make <bin|test>"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Make release binary
bin: $(OBJ_DIR)/main.o $(PROD_LIB)
	@echo "linking $@"
	@gcc $^ $(C_FLAGS) -o $@

# Make unit test suite
test: $(PROD_LIB) $(FAKE_OBJ) $(TEST_OBJ)
	@echo "linking $@"
	@g++ $(TEST_OBJ) -lc $(PROD_LIB) $(GTEST_LIBS) $(CC_FLAGS) -o $@

# Make production code library
$(PROD_LIB): $(OBJ)
	@echo "creating archive $@"
	@ar rc $@ $(OBJ)

# Include dependencies
DEP = $(OBJ:%.o=%.d)
-include $(DEP)

# Compile main
$OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	@echo "compiling $(notdir $<)"
	@gcc $< $(C_FLAGS) $(INC) -c -MMD -o $@

# Compile program source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "compiling $(notdir $<)"
	@gcc $< $(C_FLAGS) $(INC) -c -MMD -o $@

# Compile fake source
$(OBJ_DIR)/%.o: $(FAKE_DIR)/%.c | $(OBJ_DIR)
	@echo "compiling $(notdir $<)"
	@gcc $< $(C_FLAGS) $(INC) -c -MMD -o $@

# Compile unit test
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc | $(OBJ_DIR)
	@echo "compiling $(notdir $<)"
	@g++ $< $(CC_FLAGS) $(TEST_INC) -I$(SRC_DIR) -c -MMD -o $@

clean:
	@echo cleaning..
	@rm -f $(OBJ_DIR)/*

debug:
	@echo "OBJ = $(OBJ)"
	@echo "TEST_DIR = $(TEST_DIR)"
	@echo "TEST_SRC = $(TEST_SRC)"
	@echo "TEST_OBJ = $(TEST_OBJ)"
