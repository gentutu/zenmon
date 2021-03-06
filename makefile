# Copyright (C) 2020 Denis Isai

# App name
TARGET = zenmon

LD = gcc

# App directories
INC_DIR := .
LIB_DIR := ../common
SRC_DIR := .
OUT_DIR := ./out

# App artifacts
INC := $(shell find $(INC_DIR) -type d | sed -e 's/^/-I/' | grep -v ".git" | tr '\n' ' ')
LIB := $(shell find $(LIB_DIR) -type d | sed -e 's/^/-I/' | grep -v ".git" | tr '\n' ' ')
SRC := $(shell find $(SRC_DIR) \( -name "*.c" \))
OBJ := $(SRC:.c=.o)
OUT := $(OUT_DIR)/$(TARGET)
FLG :=

# make
$(TARGET):
	mkdir -p $(OUT_DIR)
	$(LD) $(SRC) $(INC) $(LIB) $(FLG) -o $(OUT_DIR)/$@ $^

# clean
clean:
	rm -rf $(OUT_DIR)
