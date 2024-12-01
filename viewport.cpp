
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

int HEIGHT_SCREEN = 850;
int WIDTH_SCREEN = 800;

SDL_Window* gWindow;
SDL_Renderer* gRender;
SDL_Texture* gTexture;

bool init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
 // WINDOW flags   
// SDL_WINDOW_FULLSCREEN: Creates a fullscreen window.
// SDL_WINDOW_OPENGL: Enables OpenGL support for the window.
// SDL_WINDOW_RESIZABLE: Allows the user to resize the window.
// SDL_WINDOW_BORDERLESS: Creates a window without a border or title bar.
// SDL_WINDOW_HIDDEN: Creates a window that is initially hidden.

    gWindow = SDL_CreateWindow("viewport test",//title
                               SDL_WINDOWPOS_CENTERED,//x
                               SDL_WINDOWPOS_CENTERED,//y
                               WIDTH_SCREEN,//width
                               HEIGHT_SCREEN,//Height
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE //flags , it take more one flag by spreat by | 
                                );

    if (gWindow == nullptr)
    {
       return false;
    }
    
    gRender = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    return true;
}

void close(){

    SDL_DestroyRenderer(gRender);
    SDL_DestroyWindow(gWindow);
    gRender = nullptr;
    gWindow = nullptr;
    SDL_Quit();

}

SDL_Texture* loadTexture(std::string path){
     
     SDL_Texture* newTexture = NULL;
     SDL_Surface* newSurface = IMG_Load(path.c_str());

     if(newSurface == NULL){
        printf("unable to load %s ,IMG ERR %s",path.c_str(), SDL_GetError());
        return NULL;
     }

    newTexture = SDL_CreateTextureFromSurface(gRender,newSurface);
    SDL_FreeSurface(newSurface);
    return newTexture;
}

int main(){

   if(!init()){
    std::cerr << "Unable to init SDL \n";
   }
   bool quit = false;
   SDL_Event e;

   while (!quit)
   {    

    // init wihte bg
    SDL_SetRenderDrawColor(gRender, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRender);

     while (SDL_PollEvent(&e) !=0)
        {
           if (e.type == SDL_QUIT)
           {
            quit = true;
           }
            
            
        }

        gTexture = loadTexture("right.bmp");
        
        //logic
        SDL_Rect   topRightViewport;
                    topRightViewport.x = WIDTH_SCREEN / 2;
                    topRightViewport.y = 0;
                    topRightViewport.w = WIDTH_SCREEN / 2;
                    topRightViewport.h = HEIGHT_SCREEN / 2;

        SDL_RenderSetViewport(gRender, &topRightViewport);

        SDL_RenderCopy(gRender,gTexture,nullptr,nullptr);
        

        // left
         gTexture = loadTexture("left.bmp");
        
        //logic
        SDL_Rect   topLeftViewport;
                    topLeftViewport.x = 0;
                    topLeftViewport.y = 0;
                    topLeftViewport.w = WIDTH_SCREEN / 2;
                    topLeftViewport.h = HEIGHT_SCREEN / 2;

        SDL_RenderSetViewport(gRender, &topLeftViewport);

        SDL_RenderCopy(gRender,gTexture,nullptr,nullptr);


        // down
         gTexture = loadTexture("down.bmp");
        
        //logic
        SDL_Rect   downViewport;
                    downViewport.x = 0 ;
                    downViewport.y = WIDTH_SCREEN / 2 ;
                    downViewport.w = WIDTH_SCREEN ;
                    downViewport.h = HEIGHT_SCREEN / 2;

        SDL_RenderSetViewport(gRender, &downViewport);

        SDL_RenderCopy(gRender,gTexture,nullptr,nullptr);

        // update the frame/screen
        SDL_RenderPresent(gRender);
   }
   
  
    close();
    return 0;
}