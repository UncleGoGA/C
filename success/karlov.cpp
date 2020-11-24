#include <iostream>

class complex{
double real;
double img;
public:
complex(){
    real = 0;
    img = 0;
}
// complex(double a, double& b = 0){
//     real = a;
//     img = b;
// }
complex(double a, double b = 0);
// complex(double a, double b);
};

// complex::complex(double a, double b = 0){
//     real = a;
//     img = b;
// }

// complex::complex(double a, double b){
//     real = a;
//     img = b;
// }

complex::complex(double a, double b){
    real = a;
    img = b;
    std::cout << "x" << std::endl;
}



// complex::complex(double a, double b){
//     real = a;
//     img = b;
//     std::cout << "x" << std::endl;
// }

int main(){
    int a = 2;
    int* p = &a;
    // complex comple(3, 2);
    complex kek(2);

    return 0;
}