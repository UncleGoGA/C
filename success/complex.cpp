#include <iostream>
#include <cstdio>
#include <cmath>

/*Task: Create class Complex numbers with all operations: *, /, +, -*/
class complex{
    double real;
    double img;
    double sinus;
    double cosinus;
public:
    complex(){
        this->real = 0;
        this->img = 0;
    }
    complex(double real, double img){
        this->real = real;
        this->img = img;
        std::cout << this << std::endl;
    }
    ~complex(){
        //std::cout << "Destruction has been start" << std::endl;
    }

    void set(){
        std::cout << "Real = ";
        std::cin >> this->real;
        std::cout << "Img = ";
        std::cin >> this->img;
    }

    void get(){
        std::cout << "Real: " << this->real << std::endl;
        std::cout << "Img: " << this->img << std::endl;
    }

    double return_real(){
        return this->real;
    }

    double return_img(){
        return this->img;
    }

    void set_real(double real){
        this->real = real;
    }

    void set_img(double img){
        this->img = img;
    }

    complex operator+(const complex& number){
        return complex(this->real + number.real, this->img + number.img);
    }
    complex operator-(const complex& number){
        return complex(this->real - number.real, this->img - number.img);
    }
    complex operator*(const complex& number){
        return complex(this->real * number.real - this->img * number.img, this->real*number.img + this->img*number.real);
    }
    complex operator/(const complex& number){
        return complex((this->real * number.real + this->img * number.img)/(pow(2, number.real) + pow(2, number.img)),(this->img * number.real - this->real * number.img)/(pow(2, number.real) + pow(2, number.img)));
    }

    complex sum(const complex fst, const complex snd){
        std::cout << "sum: " << std::endl;
        complex semi;
        semi.real = fst.real + snd.real;
        semi.img = fst.img + snd.img;
        return semi;
    }

    complex desum(const complex fst, const complex snd){
        std::cout << "desum: " << std::endl;
        complex semi;
        semi.real = fst.real - snd.real;
        semi.img = fst.img - snd.img;
        return semi;
    }

    complex multiply(const complex snd){
        complex complex;
        complex.set_real(this->real * snd.real - this->img * snd.img);
        complex.set_img(this->real * snd.img + this->img * snd.real);
        return complex;
    }

    complex del(const complex snd){
        complex complex;
        complex.real = (this->real * snd.real + this->img * snd.img)/(pow(2, snd.real) + pow(2, snd.img));
        complex.img = (this->img * snd.real - this->real * snd.img)/(pow(2, snd.real) + pow(2, snd.img));
        return complex;
    }

    void set_sin(){
        this->sinus = (exp(this->img) - exp(pow(-1, this->img)))/2; 
    }

    void set_cos(){
        this->cosinus = (exp(this->real) + exp(pow(-1, this->real)))/2;
    }

    void multilply(const complex snd){
        std::cout << "multiply: " << std::endl;
        double semi_real = 0;
        double semi_img = 0;
        semi_real = this->real * snd.real - this->img * snd.img;
        semi_img = this->real * snd.img + this->img * snd.real;
        this->set_img(semi_img);
        this->set_real(semi_real);
    }

    void delim(const complex &snd){
        std::cout << "multiply: " << std::endl;
        double semi_real = (this->real * snd.real + this->img * snd.img)/(pow(2, snd.real) + pow(2, snd.img));
        double semi_img = (this->img * snd.real - this->real * snd.img)/(pow(2, snd.real) + pow(2, snd.img));
        this->set_real(semi_real);
        this->set_real(semi_img);
    }

    void print();
};

void complex::print(){
    std::cout << "Real: " << this->real << std::endl;
    std::cout << "Img: " << this->img << std::endl;
}


int main(){
    complex fst, snd;

    fst.get();
    snd.get();

    fst.set();
    snd.set();
    fst.get();
    snd.get();

    fst = fst.sum(fst, snd);
    fst.get();

    snd = snd.desum(fst, snd);
    snd.get();

    fst.multilply(snd);
    fst.get();

    snd.delim(fst);
    snd.get();

    fst.print();

    return 0;
}