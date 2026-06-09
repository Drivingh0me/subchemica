CC = gcc

TARGET = subchemica

SRC_DIR := src
BUILD_DIR = build
# BIN_DIR = bin
INCLUDE_DIR = include

# This selects the paltform
ifeq ($(shell uname -s),Darwin)
	PLATFORM := Darwin
endif

ifeq ($(shell uname -s),Linux)
	PLATFORM := Linux
endif

PLATFORM_DIR = platform/$(PLATFORM)

SRCS := $(wildcard $(SRC_DIR)/*.c)
PLAT_SRC := $(wildcard $(PLATFORM_DIR)/*.c)
# $(info $$SRCS is [${SRCS}])

# OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
PLAT_OBJ := $(patsubst $(PLATFORM_DIR)/%.c, $(BUILD_DIR)/%.o, $(PLAT_SRC))

CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)
CT_FLAGS = -Wall -Wextra
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS) $(PLAT_OBJ)
	$(CC) $^ $(CT_FLAGS) -o $(BUILD_DIR)/$(TARGET)

# $(PLAT_OBJ): $(PLAT_SRC)
# 	$(CC) -c $< $(CFLAGS) -o $@
#
# $(OBJS): $(SRCS)
# 	mkdir -p $(BUILD_DIR)
# 	$(CC) -c $< $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(PLATFORM_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

# debug: CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -g -O0
# debug: clean $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	# rm $(BUILD_DIR)/*.o

# .PHONY: all clean debug
.PHONY: all clean
