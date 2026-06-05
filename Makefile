CC = gcc

TARGET = subchemica

SRC_DIR = src
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

SRCS = $(wildcard $(SRC_DIR)/*.c platform/$(PLATFORM)/*.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -O2
LDFLAGS =

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -g -O0
debug: clean $(TARGET)

clean:
	rm -rf $(BIN_DIR)
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean debug
