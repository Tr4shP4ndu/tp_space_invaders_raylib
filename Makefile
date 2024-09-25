.PHONY: all clean

# Define project variables
PROJECT_NAME        ?= game
RAYLIB_VERSION      ?= 5.0.0
RAYLIB_PATH         ?= ../..
COMPILER_PATH       ?= C:/raylib/w64devkit/bin
PLATFORM            ?= PLATFORM_DESKTOP
BUILD_MODE          ?= RELEASE
RAYLIB_LIBTYPE      ?= STATIC

# Cross-platform detection
ifeq ($(OS),Windows_NT)
    PLATFORM_OS = WINDOWS
    export PATH := $(COMPILER_PATH):$(PATH)
else
    UNAMEOS = $(shell uname)
    ifeq ($(UNAMEOS),Linux)
        PLATFORM_OS = LINUX
    else ifeq ($(UNAMEOS),Darwin)
        PLATFORM_OS = OSX
    endif
endif

# Compiler setup
CC = g++
ifeq ($(PLATFORM_OS),OSX)
    CC = clang++
endif

# Build mode flags
CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces
ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

# Include and Library paths
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external
LDFLAGS = -L$(RAYLIB_PATH)/src

ifeq ($(PLATFORM_OS),WINDOWS)
    LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else ifeq ($(PLATFORM_OS),LINUX)
    LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(PLATFORM_OS),OSX)
    LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit
endif

# Source and Object files
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(PROJECT_NAME)

# Link the final executable
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(PROJECT_NAME)*
	@echo Cleaning done
