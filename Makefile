CC = gcc

TARGET = subchemica

SRC_DIR := src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# This selects the paltform
ifeq ($(shell uname -s),Darwin)
	PLATFORM := macos
endif

ifeq ($(shell uname -s),Linux)
	PLATFORM := Linux
endif

PLATFORM_DIR = platform/$(PLATFORM)

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(PLATFORM_DIR)/*.c)
# $(info $$SRCS is [${SRCS}])

# OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -O2
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $< $(CFLAGS) -o $(BUILD_DIR)/$(TARGET)

$(OBJS): $(SRCS)
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CC) -c $< $(CFLAGS) -o $(BUILD_DIR)/$@

# debug: CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -g -O0
# debug: clean $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm $(BUILD_DIR)/*.o

# .PHONY: all clean debug
.PHONY: all clean
