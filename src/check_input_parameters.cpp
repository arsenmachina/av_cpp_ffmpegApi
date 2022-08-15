#include <iostream>


bool check_input_parametrs(int argc){

    if(argc < 2 ){
        std::cout << "No Input file! " << std::endl;
        return false;
    }
    
    return true;
}