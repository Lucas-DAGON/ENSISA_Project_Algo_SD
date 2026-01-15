# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O -g
CPPFLAGS := -Iinclude

# Build directory
BUILD_DIR := build

# Create build/binary directory if it doesn't exist
$(shell [ -d $(BUILD_DIR) ] || mkdir $(BUILD_DIR) 2> /dev/null || powershell -NoProfile -Command "if (-not (Test-Path -Path '$(BUILD_DIR)')) { New-Item -ItemType Directory -Path '$(BUILD_DIR)' | Out-Null }")

# --- TD1 Exercice 1 ---
SRC := src
INCLUDE := include
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)
TARGET := $(BUILD_DIR)/debug.exe

.PHONY: all create_binary clean help

all: create_binary

# Top-level rules for binary targets
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) -I$(INCLUDE) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR) 2> /dev/null || powershell -NoProfile -Command "if (-not (Test-Path -Path '$(BUILD_DIR)')) { New-Item -ItemType Directory -Path '$(BUILD_DIR)' | Out-Null }"

create_binary: $(TARGET)
	@echo "\nBuilding binary..."
	@echo "\nBuild successful (built $(TARGET))"

# Inclusion des fichiers de dépendance (if present)
-include $(DEPS) $(DEPS_TD1_EX2)


clean:
	@echo "Cleaning build directory..."
	-@rm -rf $(BUILD_DIR) 2> /dev/null || powershell -NoProfile -Command "if (Test-Path -Path '$(BUILD_DIR)') { Remove-Item -Recurse -Force '$(BUILD_DIR)' }"

help:
	@echo "Makefile to compile each exercise independently"
	@echo "usage:"
	@echo "  make         - Compile all exercises (build-only targets)"
	@echo "  make td1_exo1 - Build TD1 exercise 1 -> $(TARGET)"
	@echo "  make td1_exo2 - Build TD1 exercise 2 -> $(TARGET_TD1_EX2)"
	@echo "  make run TD1_EX=1 - Build & run TD1 exercise 1"
	@echo "  make run TD1_EX=2 - Build & run TD1 exercise 2"
	@echo "  make clean   - delete all generated files in $(BUILD_DIR)"