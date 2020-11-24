#include <iostream>

struct A{
    char t;
    char t1;
    int many;
    int cany;
};

int main(){
    char c;
    char d;
    char A::*p = &A::t1;

    std::cout << sizeof(p) << " " << sizeof(A) << std::endl;

    //char *q = reinterpret_cast<char*>(p);
    char *q = &c;
    char *r = &d;
    std::cout << "*" << (long int)q << "* *" << (long int)r << "*" << std::endl;

    q = r + 1;
    for (int i = 0; i < sizeof(p); i++)
        std::cout << (int)q[i] << " ";
    std::cout << std::endl;

    std::cout << p << std::endl;

    return 0;
}