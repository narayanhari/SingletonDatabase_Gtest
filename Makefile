#compiler and flags
CXX	= g++
CXXFLAGS = -g -O0 -std=c++17 -I$(GTEST_INC) -I$(BOOST_INC)

#GTEST Linking
GTEST_DIR = $(shell brew --prefix googletest)
GTEST_INC = $(GTEST_DIR)/include
GTEST_LIB = $(GTEST_DIR)/lib

#boost linking
BOOST_DIR = $(shell brew --prefix boost)
BOOST_INC = $(BOOST_DIR)/include
BOOST_LIB = $(BOOST_DIR)/lib

LDFLAGS = -pthread -L$(GTEST_LIB) -L$(BOOST_LIB) -lgtest -lgtest_main

#sources 

SRC = Singleton.cpp SingletonTests.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = singleton_tests

.PHONY: all clean

all: $(TARGET)
	@echo "\n>>Running Tests: "
	@./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

#clean

clean:
	rm -rf $(OBJ) $(TARGET)

