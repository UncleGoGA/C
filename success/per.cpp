#include <iostream>

class A{
public:
int a;
};
class B:public A{
public:
int b;
int* c;
};



int main(){
A a;
int* p = &a.a;
std::cout << p << '\t' << *p << std::endl;
a.a = 5;
std::cout << p << '\t' << *p << std::endl;

}