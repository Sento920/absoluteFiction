#ifndef TEXT_HANDLE 
#define TEXT_HANDLE
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<thread>
#include<chrono>

class Texthandle{
public:
    Texthandle(std::string filepath);
    //std::List<Room> Path;
    //Room getPreviousRoom();
    std::string getLine();
    std::string getPastLine();
    void getFile(std::string filepath);
    bool isGood();
    bool verifyFile(std::string filepath);
    void shutdown();
    //Returns the end of the tag's position to start at.
    int getTag(std::string tag, std::string& line);
    int getSpeed();
    bool isBold();
    bool isItal();
    std::vector<std::string> pastLines;
    std::ifstream sourceStream;
    int pastLineLoc;
    void print(std::string line);
private:
    bool bold;
    bool ital;
    int speed;
};
#endif
