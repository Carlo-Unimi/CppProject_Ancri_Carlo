# Nome dell'eseguibile
TARGET = project

# Directory sorgenti e include
SRC_DIR = src
INC_DIR = include

# File sorgente e oggetti
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRCS))

# Compilatore e flag
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INC_DIR)

.PHONY: all clean

# Regola di default
all: $(TARGET)

# Link dell'eseguibile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilazione file oggetto
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pulizia
clean:
	rm -f $(OBJS) $(TARGET)