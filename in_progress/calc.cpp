#include <iostream>
//#include "parse.h"
//#include "calculate.h"
#include <string>
#include <vector>
#include <string.h>

int main(int argc, char* argv[]){

    if(argc == 1){
        std::cout << "Incorrect input, enter any operator and operation, expl: calc 2 + 2" << std::endl;
        return 0;
    }

    /*in this func we process input, to find errors
    then we parse input to create rpn(reverse polish notation) with it, it will do in parse.h
    after it we send processed rpn to calculate.h and it returns us result
    */
    
    std::vector<std::string>input_value;
    for(size_t i = 1; i < argc; ++i){
        input_value.push_back(argv[i]);
    }

    std::string wall;
    wall;
   
return 0;
}