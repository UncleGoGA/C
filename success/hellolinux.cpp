#include <iostream>

void resize(int* mas){
    delete[] mas;
    mas = new int[20];
    for(size_t i = 0; i < 20; ++i){
        mas[i] = i;
    }
}

void resize1(int*& mas){
    delete[] mas;
    mas = new int[20];
    for(size_t i = 0; i < 20; ++i){
        mas[i] = i;
    }
}

int main(){
    int* mas = new int[10];
    int* mas1 = new int[10];
    for(size_t i = 0; i < 10; ++i){
        mas[i] = i;
        mas1[i] = i;
    }
    resize(mas);
    std::cout << "resize" << std::endl;
    for(size_t  i = 0; i < 40; ++i){
        std::cout << mas[i] << std::endl;
    }

    resize1(mas1);
    std::cout << "resize1" << std::endl;
    for(size_t i = 0; i < 20; ++i){
        std::cout << mas1[i] << std::endl;
    }

    return 0;
}