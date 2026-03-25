CXX := clang++
CXXFLAGS := -std=c++17 -stdlib=libc++ -Wall -Wextra -pedantic
TARGET := rb
SRC := main.cpp
TEST_TARGET := /tmp/rb_tests
TEST_SRC := tests.cpp

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SRC) redblack.h redblack.tpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TEST_TARGET): $(TEST_SRC) redblack.h redblack.tpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

test: $(TEST_TARGET)
	$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
