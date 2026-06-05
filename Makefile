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
	PLATFORM := linux
endif

PLATFORM_DIR = platform/$(PLATFORM)

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(PLATFORM_DIR)/*.c)
# $(info $$SRCS is [${SRCS}])

OBJS = $(SRCS:.c=.o)
# OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -O2
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

$(OBJS): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

debug: CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -g -O0
debug: clean $(TARGET)

clean:
	# rm -f $(BUILD_DIR)/$(OBJS) $(TARGET)
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean debug
