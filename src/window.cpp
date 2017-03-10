#include "window.h"

SDL_Window::SDL_Window(){
    gWindow = NULL;
    gScreenSurface = NULL;
    this->SCREEN_WIDTH = 640;
    this->SCREEN_HEIGHT = 480;
}

SDL_Window::SDL_Window(int Swidth, int Sheight){
    gWindow = NULL;
    gScreenSurface = NULL;
    this->SCREEN_WIDTH = Swidth;
    this->SCREEN_HEIGHT = Sheight;
}

bool SDL_Window::Initialize(){
   if(SDL_Init (SDL_INIT_VIDEO) >= 0){
        gWindow = SDL_CreateWindow("AbsoluteFiction",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow != NULL){
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            return true;
        }else{
            std::printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        }
   } else{
    std::printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
   }
   return false;
}

SDL_Surface* SDL_Window::LoadSurface(std::string path){
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::printf("Unable to load image %s! SDL_ERROR: %s\n", path.c_str(), SDL_GetError());
    }else{
        loadedSurface = SDL_ConvertSurface(loadedSurface,gScreenSurface->format,0);
    }
    return loadedSurface;
}

void SDL_Window::Close(){
    // Free up our Surface Image
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

    std::printf("Shutting Down SDL...\n");
}

SDL_Surface* SDL_Window::GetScreenSurface(){
    return gScreenSurface;
}

void SDL_Window::UpdateWindow(){
    SDL_UpdateWindowSurface(gWindow);
}

SDL_Surface* SDL_Window::StretchToScreen(SDL_Surface* surface){
    return SDL_ConvertSurface(surface, this->gScreenSurface->format,0);
}

int SDL_Window::GetScreenWidth(){
    return this->SCREEN_WIDTH;
}

int SDL_Window::GetScreenHeight(){
    return this->SCREEN_HEIGHT;
}

