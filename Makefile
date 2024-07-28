# Compiler and flags
CXX = mpic++
CXXFLAGS = -Wall -Wextra -O2

# Target executable name
TARGET = mpi_simulation

# Source files
SRCS = src/main.cpp src/models/mpi_box_muller.cpp src/utils/random_generator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Include directories
INCLUDES = -I src/utils -I src/models

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
