#ifndef TEXT_HANDLE 
#define TEXT_HANDLE
#include<string>
#include<fstream>
#include<iostream>
#include<vector>

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
    void getTag(std::string tag, std::string& line);
    int getSpeed();
    std::vector<std::string> pastLines;
    int pastLineLoc;
    std::ifstream sourceStream;
private:
    int speed;
};
#endif
