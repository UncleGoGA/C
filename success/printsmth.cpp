#include <iostream>

int main(){
    std::string string;

    std::cin >> string;
    for(size_t i = 0; i < string.size(); ++i){
        std::cout << string[i];
        std::cout.flush();
    }
    std::cout << std::endl;


    return 0;
}