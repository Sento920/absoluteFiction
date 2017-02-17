#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<thread>
#include<chrono>

#include "player.h"
#include "battle.h"
#include "texthandler.h"

using std::string;
using std::vector;
using std::cout;

void print(string line, int speed);
void print(string line);

int main (int argc, char* argv[]){
    cout << "Starting Up..." << std::endl;
    if(argc == 2){
        string file(argv[1]);
        Texthandle input(file);
        while(input.isGood()){
            print(input.getLine(),input.getSpeed());
        }
        input.shutdown();
    }else{
        cout << "Please Input at least one text document to play.\nExiting..." << std::endl;
    }
    return 0;
}

void print(string line, int speed){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(speed * 50));
    }
    cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(speed * 50));
}

void print(string line){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
    cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(50));
}

