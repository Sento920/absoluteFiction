#ifndef SDL_WINDOW
#define SDL_WINDOW

#include<string>
#include<cstdio>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class SDL_Window{
    public:
        SDL_Window();
        SDL_Window(int Swidth, int Sheight);
        bool Initialize();
        SDL_Surface* LoadSurface(std::string path);
        void UpdateWindow();
        void Close();
        SDL_Surface* GetScreenSurface();
        SDL_Surface* StretchToScreen(SDL_Surface* surface);
        typedef enum KeyPressSurfaces{
            KEY_PRESS_SURFACE_DEFAULT,
            KEY_PRESS_SURFACE_UP,
            KEY_PRESS_SURFACE_DOWN,
            KEY_PRESS_SURFACE_LEFT,
            KEY_PRESS_SURFACE_RIGHT,
            KEY_PRESS_SURFACE_TOTAL,
        } KPS;
        int GetScreenWidth();
        int GetScreenHeight();
   private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        SDL_Window* gWindow;
        SDL_Surface* gScreenSurface;
};
#endif
