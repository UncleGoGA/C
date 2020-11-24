#include <math.h>
#include <iostream>

typedef double (*f1)(double);

typedef double (*udvoen)(double, double, int, f1 g); //для удобства 

double check_val(double a, double b) // Проверка результатов по формуле ньютона-лейбница

{

    return b * b / 2 - a * a / 2;
}

double g(double x)

{

    return (1 - x*x) / pow((1 + x*x), -1);
}

double method(double a, double b, int n, f1 g) // По формуле прямоугольников

{

    double result;

    double S = 0;

    double h, xi;

    int i = 0;

    h = (b - a) * 1.0 / n;

    for (i = 1; i <= n; i++)

    {

        xi = a + i * h;

        S = S + g(xi);
    }

    result = h * S;

    return result;
}

double udvoenie(double a, double b, double eps, int n, udvoen y, f1 g) // Метод удвоения числа шагов

{

    double I1, I2;

    I1 = 0;

    I2 = eps + 1;

    n = 10;

    while (fabs(I2 - I1) > eps) //будет сравнивать каждый аргумент сокрытый в typedef`е
    {

        I1 = I2;

        I2 = y(a, b, n, g);

        n *= 2;
    }

    return I2;
}

int main()

{
    double integral, check;

    int n = 10;
    f1 f;
    double a, b, c, d, eps;

    printf("Введите нижнюю границу первого интеграла: ");

    scanf("%lf", &a);

    printf("Введите верхнюю границу первого интеграла: ");

    scanf("%lf", &b);

    printf("Введите нижнюю границу второго интеграла: ");

    scanf("%lf", &c);

    printf("Введите верхнюю границу второго интеграла: ");

    scanf("%lf", &d);

    printf("Введите точность: ");

    scanf("%lf", &eps);

    check = check_val(a, b);

    integral = udvoenie(a, b, eps, n, method, f);

    printf("%lf \n", integral);

    printf("Проверка результата по формуле Ньютона-Лейбница: ");

    printf("%lf %lf\n", integral, check);

    printf("Интеграл: %lf\n", udvoenie(c, d, eps, n, method, g));

    return 0;
}