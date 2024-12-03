#include "texture.h"
#include <SDL_image.h>
#include <stdexcept>

class LTexture : public ITexture
{
private:

   SDL_Renderer* gRenderer;

   SDL_Texture* gTexture;

   int mWidth;

   int  mHeight;

public:

   explicit LTexture(SDL_Renderer* reneder): gRenderer(reneder), gTexture(nullptr), mWidth(0), mHeight(0){}

    ~LTexture(){

        free();

    }

    bool loadFromFile(const std::string& path) const override {
        
        free();
        
        SDL_Surface* imageSurface = IMG_Load(path.c_str());

        if(imageSurface == nullptr){

            throw std::runtime_error("Unable to load image at " + path + " :: SDL Error: " + std::string(SDL_GetError()));

        }
        
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0, 0xFF, 0xFF));
        
        gTexture = SDL_CreateTextureFromSurface(gRenderer,imageSurface);

        mWidth = imageSurface->w;

        mHeight = imageSurface->h;

         SDL_FreeSurface(imageSurface);

        return true;
    }

    SDL_Texture* getTexture()const override {

        return gTexture;

    }

    int getWidth() const override {

        return mWidth;
    
    }

    int getHeight() const override {

        return mHeight;
    
    }

    void render(int x, int y) override {
        
        SDL_Rect queued  = {x,y, mWidth, mHeight};

        SDL_RenderCopy(gRenderer,gTexture,NULL, &queued);
    }

    void free() const {

        if (gTexture)
        {
        
        SDL_DestroyTexture(gTexture);
        
        gTexture = nullptr;

        mHeight = 0;

        mWidth = 0;

        }
        
    }

};


