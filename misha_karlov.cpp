#include <iostream>

#define CONST_APROX 0

class vector{
    long double** matrix;
    size_t rows, cols;
    size_t len(long double* pm){
        long double* p = pm;
        while(*pm)++pm;
        return pm - p;
    }
    size_t capacity, size;
public:
    vector(long double value = 0){ //какая же хуета
        cols = rows = 1;
        matrix = new long double* [rows];
        matrix[0] = new long double [cols];
        capacity = size = 1;
    }
    vector(const vector& matr){
        rows = matr.rows;
        cols = matr.cols;
        capacity = matr.capacity;
        size = matr.size;
        for(size_t i = 0; i < rows; ++i)
        delete[] matrix[i];
        delete[] matrix;
        matrix = new long double* [rows];
        for(size_t i = 0; i < rows; ++i){
            matrix[i] = new long double [cols];
        }
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < cols; ++j){
                matrix[i][j] = matr.matrix[i][j];
            }
        }
    }
    ~vector(){
        for(size_t i = 0; i < rows; ++i){
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void push_back(long double value){
        if(size == capacity){
            
        }
    }

};

class iterator{


};

class interface{


};


int main(){

    return 0;
}