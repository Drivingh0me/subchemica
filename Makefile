# Add help

PROJECT := subchemica
INCLUDE_DIR := include
BIN_DIR = bin
# LIB_DIR := lib
SRC_DIR := src
BUILD_DIR := build
PLATFORM_DIR := platform/macos

STACK_USAGE := -fstack-usage

CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)
# LDFLAGS := -L$(LIB_DIR)

# all: $(BUILD_DIR)/$(PROJECT)

SRCS := $(wildcard $(SRC_DIR)/*.c $(PLATFORM_DIR)/*.c)

# print-srcs:
# 	@echo $(SRCS)

OBJS := $(patsubst $(SRC_DIR)/%.c $(PLAFORM_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
# print-objs:
# 	@echo $(OBJS)

all: $(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $^

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
$(BUILD_DIR)/%.o: $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)

exec: $(BUILD_DIR)/$(PROJECT_NAME)
	./$(BUILD_DIR)/$(PROJECT_NAME)

.PHONY: all clean exec
