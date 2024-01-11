CXX = g++
CXXFLAGS = -std=c++11
SRC_DIR = src
BUILD_DIR = build
EXEC = library_management_system

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean
