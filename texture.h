#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

// Forward declaration to avoid including SDL here
struct SDL_Texture;

class ITexture {

public:

    virtual ~ITexture() = default;

    // Load image at the specified path
    virtual bool loadFromFile(const std::string& path) = 0;

    // Render texture at the given point
    virtual void render(int x, int y) = 0;
    virtual void render(int x, int y, SDL_Rect* clip= nullptr) = 0;
    // Get image dimensions
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    // Get the underlying SDL texture (optional)
    virtual SDL_Texture* getTexture() const = 0;
    // Deallocate texture
    virtual void free() = 0;
};

#endif // TEXTURE_H
