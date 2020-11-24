#include <iostream>
#include <stdio.h>
#include <cstring>

template<typename T>
class myvector{
    T* array;
    size_t size; //includes some upper size
    size_t lenght; //how much elements
    //T* pointer mb use list to add elements like push_back
    T* create_array(const size_t size){ //stupid allocator without any control
        T* arr = new T[size];
        memset(arr, NULL, size);
        return arr;
    }
    void insert_values(const size_t lenght, const T* value, T*& array){
        for(size_t i = 0; i < lenght; ++i){
            this->array[i] = value[i];
        }
    }
public:
    size_t len(){
        T* start = this->value;
        while(*value){
            this->value++;
        }
        return value - start;
    }
    myvector(){
        this->array = create_array(5);
        this->size = 5;
        this->lenght = 0;
    }
    myvector(T* value){
        //this->value = value; we need to copy elements, not to change pointer on first element
        this->lenght = len(value);
        this->size = lenght + (lenght*0.3);
        this->array = create_array(size);
        insert_values(lenght, value, this->array);
    }
    ~myvector(){
        delete[] this->array;
        this->array = nullptr;
    }
    void push_back(T value){
        if(lenght < size){
            this->array[lenght] = value; 
        }
        else{
            
        }
    }
    void show(){ //debug show
        for(size_t i = 0; i < this->size; ++i){
            std::cout << this->array[i] << std::endl;
        }
    }

};
// myvector operator {}::myvector{

// } it can realized by std::initial_list



int main(){

    return 0;
}