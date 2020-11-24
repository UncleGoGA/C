#include <iostream>
#include <exception>
#include <typeinfo>

class A{
int *c;
static const int n = 5;
public:
A(){
    printf("Constuct");
    c = new int;
}
~A(){
    std::cout << "Destruct" << std::endl;
    delete c;
}
A* operator=(A b){
    c = b.c;
    return &*this;
}
};

void b(){
    std::cout << "B" << std::endl;
    throw(1);
}

void alg(){
    try {
        b();
    }
    catch(const int a){
        //std::cout << a << std::endl;
    }
    
    
}

int main(){

    A a;
    alg();
    std::cout << typeid(kk()).name() << std::endl;
    std::bad_typeid bt;
    std::cout << bt.what() << std::endl;
    //exit(0);
    _Exit(0);
    return 0;
}