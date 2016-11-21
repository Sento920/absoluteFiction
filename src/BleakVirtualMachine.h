#ifndef _BLEAKVIRTUALMACHINE_H_
#define _BLEAKVIRTUALMACHINE_H_

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>



using std::string;

class BleakVirtualMachine{

    
public:
    
    static const int INSTRUCTION_OUT_OF_BOUNDS;
    static const int INPUT_OUT_OF_BOUNDS;
    static const int UNKNOWN_INSTRUCTION;
    std::vector<int> input_list;
    std::vector<int> output_list;
    std::vector<string> inst_list;
    std::map<std::string,int> Labels;
    std::map<std::string,int> Registers;
    // r0...r9, pc, nc, ra.
    
    BleakVirtualMachine(const std::string source, const std::string input);
        //Constructor
    
     void Reset();
        // Resets all the Registers etc
    
     const std::vector<string> GetInstructions() const;
        // returns constant vector of tolkenized instructions.
    
     const std::vector<int> GetInput() const;
        // Returns input to the VM
    
     const std::vector<int> GetOutput() const;
        // Returns output to the VM
    
     std::map<string,int>& GetRegisters();
        // Maps registers to the respective strings.
    
     const std::map<string,int> GetLabels() const;
        // Maps Labels to respective addresses.
    
     string ResolveLValue(const std::string expr);
        //returns string of register name, takes in an expression. [] indicates indirect addresses.
    
     int ResolveRValue(const std::string expr);
        // returns string of register name, takes in an expression. [] indicated indirect addresses.
    
     static std::vector<string> Tokenize(const std::string &token);
        // takes in a whitespace delimited list of strings, puts out a tolkenized vector.
    
     void Step();
        // ??? yea, go decode the spec some more. GOOD LUCK.
    
};

#endif
