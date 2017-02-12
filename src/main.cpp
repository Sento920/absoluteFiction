#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<thread>
#include<chrono>

#include "player.h"
#include "battle.h"


using std::string;
using std::vector;
using std::cout;

void print(string line, int speed);
void print(string line);

int main (int argc, char* argv[]){
    string hi = "Hello World, This is a test";
    print( hi , 3 );
    print ("This is a second test.");
    return 0;
}

void print(string line, int speed){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(speed * 50));
    }
    cout << std::endl;
}


void print(string line){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
    cout << std::endl;
}
