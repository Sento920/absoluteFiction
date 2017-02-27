#include"texthandler.h"

using std::stringstream;
using std::string;
using std::cout;
using std::cerr;

    Texthandle::Texthandle(std::string filepath){
        pastLineLoc = 0;
        speed = 1;
        bold = false;
        ital = false;

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
            /*while(line.find('[') != npos){
                int pos = line.find_first_of(']');
                std::string tag = line.substr
            
            }*/
        }
        return line;
    }

    bool Texthandle::isBold(){
        return bold;
    }

    bool Texthandle::isItal(){
        return ital;
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
        string temp = "";
        if(tag.length() > 0){
            for( unsigned int c = 0; c < tag.length(); c++){
                if(tag[c] == 's'){
                    //speed change
                    int n = c+1;
                    while((char) tag[n] > 47 && (char) tag[n] <58){
                        temp += tag[n];
                        n++; 
                    }
                    c = n;
                    if(temp.length()){
                        this->speed = std::stoi(temp.c_str());
                    }
                }else if(tag[c] == 'b'){
                    //bolded letter
                    if(bold){
                        //cout << "\e1m";
                        bold = false;
                    }else{
                        //cout << "\e0m";
                        bold = true;
                    } 

                }else if(tag[c] == 'i'){
                    //Italics active  

                }else if(tag[c] == 'c'){
                    //Color change

                }else if(tag[c] == 'p'){
                    //Player Construct
                    
                }
                int i = line.find(tag);
                if(i > 0){
                    line.erase(i-1,tag.length()+2);
                }          
	    }
        }else{
            cerr << "Improper Tag Detected." << std::endl;
        }

    }
   
   void Texthandle::print(string line, int speed){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(speed * 50));
    }
    cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(speed * 50));
}

void Texthandle::print(string line){
    for(unsigned int i = 0; i < line.length(); i++){
        cout << line[i] << std::flush;
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
    cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(50));
}
   
   
    int Texthandle::getSpeed(){
        return speed;
    }

