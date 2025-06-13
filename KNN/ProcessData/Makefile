# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall -O2

# Build directory for object files
BUILD_DIR = build

# Source files
SRCS = $(wildcard *.cpp)
# Object files in build directory
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
# Output executable
TARGET = process_data.exe

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 2>nul || true

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET) 2>nul || rm -f $(BUILD_DIR)/*.o $(TARGET)
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) 2>nul || rm -rf $(BUILD_DIR)

.PHONY: all clean
	