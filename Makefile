TARGET_EXEC ?= a.out

BUILD_DIR ?= ./Build
SRC_DIRS ?= ./Src

CFLAGS :=
LDFLAGS := $(shell pkg-config --libs sfml-all)
CC := g++

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

.DEFAULT_GOAL := build
.PHONY: build clean

build:
	$(CC) $(CFLAGS) $(shell find . -name *.cpp -or -name *.c -or -name *.s) -o a.out $(LDFLAGS)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

