CXX = g++
CXXFLAGS = -std=c++11 -IC:/OpenCV/include
LDFLAGS = -LC:/OpenCV/x64/mingw/lib
LIBS = -lopencv_core455 -lopencv_imgcodecs455 -lopencv_highgui455

SRC = main.cpp Image_process.cpp kmeans.cpp
OBJ_DIR = build
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET = compress_image_kmeans

# Mục mặc định
all: $(TARGET)

# Tạo file thực thi từ các object
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

# Tạo thư mục build nếu chưa tồn tại và biên dịch từng file cpp
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tạo thư mục build nếu chưa có
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Dọn dẹp
clean:
	del /Q $(OBJ_DIR)\*.o $(TARGET)
