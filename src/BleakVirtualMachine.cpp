#include "BleakVirtualMachine.h"


const int BleakVirtualMachine::INSTRUCTION_OUT_OF_BOUNDS = 1;
const int BleakVirtualMachine::INPUT_OUT_OF_BOUNDS = 2;
const int BleakVirtualMachine::UNKNOWN_INSTRUCTION = 3;


BleakVirtualMachine::BleakVirtualMachine(const std::string source, const std::string input){
    Reset();
    std::ifstream sourceStream;
    sourceStream.open(source);
    std::ifstream inputStream;
    inputStream.open(input);
    int i = 0;
    while(!sourceStream.eof()){
        string temp;
        getline(sourceStream,temp);
        std::stringstream line(temp);
        if(temp != "")
            inst_list.push_back(temp);
        
        std::cout << temp << std::endl;
        while(line){
            line >> temp;
            if(temp == "<-"){
                line >> temp;
                Labels[temp] = i;
            }
        }
        i++;
    }
    while(!inputStream.eof()){
        string x;
        int c = 0;
        getline(inputStream,x);
        std::stringstream buffer(x);
        buffer >> c;
        //std::cout << x;
        if(c != 0){
            input_list.emplace_back(c);
        }
    }
    sourceStream.close();
    inputStream.close();
}

void BleakVirtualMachine::Reset(){
    // Resets any and all registers, should initialize the values to zero, non-indirectly addressed.
    BleakVirtualMachine::Registers["r0"] = 0;
    BleakVirtualMachine::Registers["r1"] = 0;
    BleakVirtualMachine::Registers["r2"] = 0;
    BleakVirtualMachine::Registers["r3"] = 0;
    BleakVirtualMachine::Registers["r4"] = 0;
    BleakVirtualMachine::Registers["r5"] = 0;
    BleakVirtualMachine::Registers["r6"] = 0;
    BleakVirtualMachine::Registers["r7"] = 0;
    BleakVirtualMachine::Registers["r8"] = 0;
    BleakVirtualMachine::Registers["r9"] = 0;
    BleakVirtualMachine::Registers["pc"] = 0;
    BleakVirtualMachine::Registers["nc"] = 0;
    BleakVirtualMachine::Registers["ra"] = 0;
    BleakVirtualMachine::output_list.clear();
}

const std::vector<string> BleakVirtualMachine::GetInstructions() const{
    return inst_list;
}

const std::vector<int> BleakVirtualMachine::GetInput() const{
    //Gets the input from the file? Not sure where we are getting the input.
    return input_list;
}

const std::vector<int> BleakVirtualMachine::GetOutput() const{
    //this method will get the output from the damned thinger I dont know about yet.
    return output_list;
}

std::map<std::string,int>& BleakVirtualMachine::GetRegisters(){
    //this method will intialize the registers, with 0. 
    //Recall that registers can be addressed indirectly, and that they are going to be linked to each other, OR to another register.
    return Registers;
}

const std::map<std::string,int> BleakVirtualMachine::GetLabels() const{
    //Maps labels to the individual addresses, which represent registers.
    return Labels;
}

std::string BleakVirtualMachine::ResolveLValue(const std::string expr){
    string L_value;
    string tmp;
    tmp = expr.substr(1,2);
    
    if(expr.at(0) == 'r'||expr.at(0) == 'p'||expr.at(0) == 'n'){
        L_value = expr;
    }else if(expr.at(0) == '['){
        L_value = 'r' + std::to_string(Registers[tmp]);
    }
    return L_value;
}

int BleakVirtualMachine::ResolveRValue(const std::string expr){
    //returns the value of the expression. uses the expression taken in to determine values.
    int r_value = 0;
    string reg;
    //R or literal
    //printf("expr: %s\n", expr.c_str());
    if(expr.at(0) == 'r' || expr.at(0) == '['){
        //this means we need a register.
        reg = ResolveLValue(expr);
        //reg now holds the register name
        r_value = Registers[reg];
    }else{
        r_value = std::atoi(expr.c_str());
        
    }
    //printf("R_Val: %d\n", r_value);
    return r_value;
}

std::vector<std::string> BleakVirtualMachine::Tokenize(const std::string &token){
    std::vector<std::string> vec; 
    std::stringstream in(token);
    std::string val;
    while(in >> val) {
        vec.push_back(val);
    }
    return vec;
}

void BleakVirtualMachine::Step(){
    //moves the program counter forward one step.
    string holder = inst_list.at(Registers["pc"]);
    std::stringstream ss(holder);
    string curr_inst;
    string lval;
    string rval;
    //grab our three possible instructions for this line, don't worry about Rval being null occasionally.
    ss >> curr_inst;
    ss >> lval;
    ss >> rval;
    printf("INFO: inst_size: %lu, input_size: %lu, out_size: %lu, PC: %d\n",inst_list.size(),input_list.size(),output_list.size(), Registers["pc"]);
    printf("INFO: curr: %s, Lval: %s, Rval: %s\n",curr_inst.c_str(),lval.c_str(),rval.c_str());
    
    if(inst_list.size()-1 < (unsigned int) Registers["pc"]){
        throw INSTRUCTION_OUT_OF_BOUNDS;
    }
    //grabbed curr_instent instruction.
    if(curr_inst == "add"){
        //Adds lval and Rval, then stores them in lval.
        Registers[ResolveLValue(lval)] = Registers[ResolveLValue(lval)] + ResolveRValue(rval);
        
    }else if(curr_inst == "sub"){
        //Subtracts Rval from Lval, stores result in lval
        Registers[ResolveLValue(lval)] = Registers[ResolveLValue(lval)] - ResolveRValue(rval);
        
    }else if(curr_inst == "inc"){
        //increments lval
        Registers[ResolveLValue(lval)] = Registers[ResolveLValue(lval)] + 1;
        
        
    }else if(curr_inst == "dec"){
        //decrements lval
        Registers[ResolveLValue(lval)] = Registers[ResolveLValue(lval)] - 1;
        
        
    }else if(curr_inst == "input"){
        //reads next input from the input list as indicated by nc, 
        //stores result in lval, increments nc
        if(input_list.size()-1 > (unsigned int) Registers["nc"]){
            Registers[ResolveLValue(lval)] = input_list[Registers["nc"]];
            Registers["nc"]++;
        }else{
            throw INPUT_OUT_OF_BOUNDS;
        }
        
    }else if(curr_inst == "output"){
        //emits lval to the output list.
        int x = ResolveRValue(lval);
        //printf("INFO: X: %d\n",x);
        output_list.emplace_back(x);
        
    }else if(curr_inst == "store"){
        //copies rval to lval
        Registers[ResolveLValue(lval)] = ResolveRValue(rval);
        
    }else if(curr_inst == "jmp"){
        // alters pc so that the next instruction is now the label.
        Registers["pc"] =  Labels[lval];
        
    }else if(curr_inst == "jpos"){
        // if Rval is positive, alters pc so that the next instruction is now the label
        if(ResolveRValue(lval) > 0)
            Registers["pc"] = Labels[rval];
        
    }else if(curr_inst == "jneg"){
        // if Rval is negative, alters pc so that the 
        if(ResolveRValue(lval) < 0)
            Registers["pc"] = Labels[rval];
    
    }else if(curr_inst == "jzilch"){
        if(ResolveRValue(lval) == 0)
            Registers["pc"] = Labels[rval];
        
    }else if(curr_inst == "call"){
        Registers["ra"] = Registers["pc"] + 1;
        Registers["pc"] = Labels[lval];
        
    }else if(curr_inst == "return"){
        Registers["pc"] = Registers["ra"];
        
    }else{
        //WE'VE BEEN HIT. RETURN FIRE!
        throw UNKNOWN_INSTRUCTION;
    }
    
    Registers["pc"]++;
}
