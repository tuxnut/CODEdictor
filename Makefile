CC=gcc
CFLAGS=-W -Wall -Wextra -pedantic -std=c99
LDFLAGS=

EXEC=code

SRC_DIR=src
OBJ_DIR=obj
BUILD_DIR=build

SRC_FILES= $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJ_FILES)
	@echo "==> Building file '$@'"
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@echo "==> Compiling '$<'"
	$(CC) $(CFLAGS) -c $< -o $@

export: $(SRC_FILES)
	tar -zcvf $(EXEC).tgz $(SRC_DIR)/* Makefile

run: $(BUILD_DIR)/$(EXEC)
	@echo "==> Starting $(EXEC)"
	./$(BUILD_DIR)/$(EXEC)

archi:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(SRC_DIR)
	touch .gitignore

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(BUILD_DIR)/$(EXEC)

