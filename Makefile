CXX := clang++
CXXFLAGS := -std=c++17 -stdlib=libc++ -Wall -Wextra -pedantic
TARGET := rb
SRC := main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) redblack.h redblack.tpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
