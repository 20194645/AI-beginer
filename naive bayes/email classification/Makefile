# Tên trình biên dịch
CXX = g++

# Cờ biên dịch
CXXFLAGS = -std=c++17 -Wall -O2

# Tên file thực thi
TARGET = main

# Danh sách tất cả file .cpp
SOURCES = $(wildcard src/*.cpp)

# Tạo danh sách file .o tương ứng
OBJECTS = $(SOURCES:.cpp=.o)

# Luật mặc định
all: $(TARGET)

# Tạo file thực thi
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Luật biên dịch file .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Luật dọn dẹp
clean:
	rm -f $(TARGET) $(OBJECTS)
