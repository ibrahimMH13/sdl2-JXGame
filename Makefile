CXX = clang++
CXXFLAGS = -I/opt/homebrew/include/SDL2 -g -O2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

# Allow user to specify SRC and OUT dynamically
SRC ?= app.cpp
OBJ = $(SRC:.cpp=.o) # Convert SRC files to object files
OUT ?= game

# Default target
all: $(OUT)

# Link all object files into the executable
$(OUT): $(OBJ)
	@echo "Linking $(OUT)..."
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile each .cpp file into an .o file
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OUT) $(OBJ)

# Run the compiled binary
run: $(OUT)
	./$(OUT)

# Help information
help:
	@echo "Usage:"
	@echo "  make               # Build the default target"
	@echo "  make SRC=foo.cpp OUT=foo # Build a specific source file"
	@echo "  make clean         # Remove the compiled binary and object files"
	@echo "  make run           # Build and run the binary"
