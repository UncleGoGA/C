#include <iostream>
#include <cstring>

class man{
int age;
char* name;
size_t name_size = 5;
public:
    man();
    man(int a,const char* b);
    // man(const man& m);
    ~man(){
        delete[] name;
    }
};

man::man(){
    age = 0;
    name = new char[name_size];
    strcpy(name, "Olya");
}

man::man(int a, const char* b = "Nastya"){
    this->age = a;
    size_t size = 0;
    while(*b){
        b++;
        size++;
    }
    this->name = new char[size+1];
    this->name_size = size;
    strcpy(name, b);
}

void p(man a, man b){

}

int main(){
    man woman;
    man realman(20, "Oleg");
    p(woman, realman);

    return 0;
}