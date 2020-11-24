#include <iostream>

class Point{
    double x, y;
    public:
    Point(double x = 0, double y = 0){
        this->x = x;
        this->y = y;
    }
    Point operator+(const Point &p){
        this->x += p.x;
        this->y += p.y;
    }
    void show(){
        printf("%f %f", x, y);
    }
};

class Triangle{
    Point x1,x2,x3;
    double x1x2, x1x3, x2x3;
    double square;
    
    public:
    static int count;
    void show(){
        printf("%s%fTriangle #", count);
        count++;
    }
};

int Triangle::count = 0;

int main(){


    return 0;
}