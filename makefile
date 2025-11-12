CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -O2

SRC = main.cpp avl.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main.e

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp avl.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
