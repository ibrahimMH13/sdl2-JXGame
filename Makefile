CXX = clang++
CXXFLAGS = -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

game: app.cpp
	$(CXX) -o game app.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f game
