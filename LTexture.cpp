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

    ~LTexture() override {

        free();

    }

    bool loadFromFile(const std::string& path)  override {
        
        free();
        
        SDL_Surface* imageSurface = IMG_Load(path.c_str());

        if(imageSurface == nullptr){

            return false;

        }
        
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0, 0xFF, 0xFF));
        
        gTexture = SDL_CreateTextureFromSurface(gRenderer,imageSurface);

        mWidth = imageSurface->w;

        mHeight = imageSurface->h;

         SDL_FreeSurface(imageSurface);

        return true;
    }

    SDL_Texture* getTexture() const override {

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

    void render(int x, int y, SDL_Rect* clip) override {

         SDL_Rect renderQueued = {x, y, mWidth, mHeight};

        if (clip)
        {
            renderQueued.h = clip->h;
            renderQueued.w = clip->w;

        }
        SDL_RenderCopy(gRenderer, gTexture, clip, &renderQueued);
    }

    void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){

      SDL_Rect  queueRender = {x, y, mWidth, mHeight};

        if (!clip)
        {
           queueRender.w = clip->w;

           queueRender.h = clip->h;
        }
        
        SDL_RenderCopyEx(gRenderer,gTexture,clip,&queueRender,angle,center,flip);
    }


    void setColor(Uint8 red, Uint8 green, Uint8 blue) override {

        SDL_SetTextureColorMod(gTexture, red, green, blue);
    }

    void setBlendMode(SDL_BlendMode blending) override {

        SDL_SetTextureBlendMode(gTexture, blending);
    }

    void setAlpa(Uint8 alpha) override {

        SDL_SetTextureAlphaMod(gTexture, alpha);
    }

    void free() override {

        if (gTexture)
        {
        
        SDL_DestroyTexture(gTexture);
        
        gTexture = nullptr;

        mHeight = 0;

        mWidth = 0;

        }
        
    }

};


