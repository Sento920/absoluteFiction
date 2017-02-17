#include"texthandler.h"

using std::stringstream;
using std::string;
using std::cout;
using std::cerr;

    Texthandle::Texthandle(std::string filepath){
        pastLineLoc = 0;
        speed = 1;
        if(verifyFile(filepath)){
            Texthandle::sourceStream.open(filepath);
            //cout << "Valid." << std::endl;
        }else{
            cerr <<"INVALID FILENAME. EXITING" << std::endl;
            Texthandle::sourceStream.close();
            exit(1);
        }
    }
    //List<Room> texthandle::Path;
    //Room texthandle::getPreviousRoom();
    std::string Texthandle::getLine(){
        std::string line;
        getline(Texthandle::sourceStream,line);
        if(line.length() > 0){
            if(line.at(0)=='['){
                int pos = line.find_first_of(']');
                std::string tag = line.substr(1,pos-1);
                getTag(tag,line);
            }
        }
        return line;
    }
    bool Texthandle::verifyFile(std::string filepath){
        std::ifstream f(filepath);
        return f.good();
    }

    std::string Texthandle::getPastLine(){
        pastLineLoc--;
        return pastLines.at(pastLineLoc);
    }

    void Texthandle::shutdown(){
        Texthandle::sourceStream.close();
        cout << "Source Closed." << std::endl;
    }

    bool Texthandle::isGood(){
        return !sourceStream.eof();
    }
    
    void Texthandle::getTag(std::string tag, std::string& line){
        //cout << "tag: " << tag << std::endl;
        //cout << "Line: " << line << std::endl;
        if(tag.length() > 0){
            for(int c = 0; c < tag.length(); c++){
				switch (tag[c])
				case ('b'):
				
					break;
				case ('i'):
				
					break;
				case ('s'):
					
					break;
				case ('p'):
				
					break;
				case default:
					cout << "Default found." << std::endl;
					break;
				
			}
        }else{
            cerr << "Improper Tag Detected." << std::endl;
        }

    }
   
    int Texthandle::getSpeed(){
        return speed;
    }

