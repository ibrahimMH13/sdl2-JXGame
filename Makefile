CXX = clang++
CXXFLAGS = -I/opt/homebrew/include/SDL2 -g -O2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

# Source file (default to app.cpp)
SRC ?= app.cpp
OUT = game

# Default target
all: $(OUT)

$(OUT): $(SRC)
	@echo "Building $(OUT) from $(SRC)..."
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS)

# Clean up generated files
clean:
	rm -f $(OUT)

# Run the compiled binary
run: $(OUT)
	./$(OUT)

# Allow the user to specify a different source file
help:
	@echo "Usage:"
	@echo "  make           # Build the default source file"
	@echo "  make SRC=foo.cpp # Build a specific source file"
	@echo "  make clean     # Remove the compiled binary"
	@echo "  make run       # Build and run the binary"
