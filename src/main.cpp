#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<thread>
#include<chrono>
#include<SDL2/SDL.h>
#include "player.h"
#include "battle.h"
#include "texthandler.h"
#include "window.h"

using std::string;
using std::vector;
using std::cout;



int main (int argc, char* argv[]){
    cout << "Starting Up..." << std::endl;
    if(argc == 2){
        string file(argv[1]);
        Texthandle input(file);
        while(input.isGood()){
            input.print(input.getLine(),input.getSpeed());
        }
        input.shutdown();

    }else if(argc == 1){
        bool quit = false;
        SDL_Window window = SDL_Window();
        if(window.Initialize()){
            string path = "img/img.jpg";
            SDL_BlitSurface(window.LoadSurface(path), NULL, window.GetScreenSurface(),NULL);
            window.UpdateWindow(); 
        }
        SDL_Event e;
        while(!quit){
            while(SDL_PollEvent( &e) != 0 ){
                if(e.type == SDL_QUIT){
                    quit = true;
                }else if( e.type == SDL_KEYDOWN){
                    std::printf("You pressed a Key!\n");
                }
            }
       }
       window.Close();
    }else{
        cout << "Please Input at least one text document to play, or Nothing to test SDL.\nExiting..." << std::endl;
    }
    return 0;
}



