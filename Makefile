SRC_DIR := algorithms/src
BUILD_DIR := algorithms/build
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) main
main: main.c
	gcc main.c -o main

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	gcc $< -o $@