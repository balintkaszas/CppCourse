#include <iostream>
#include <cmath>


double f(double x){
    return cos(x)*exp(-(x*x));
}

//pseudocode from https://rosettacode.org/wiki/Numerical_integration
double integrate(int n, double x0, double x1){

    double step = (x1 - x0) / n;

    double sum1 = f(x0 + step * 0.5);
    double sum2 = 0.;

    for(int i = 1; i <= n ; ++i){
        sum1 += f(x0 + step*i + step * 0.5);
        sum2 += f(x0 + step*i);
    }
    return (step/6.)*(f(x0) + f(x1) + 4.*sum1 + 2.*sum2);
}

int main(){
    std::cout.precision(16);
    const double realValue = 1.34638795680345037669816;
    double value = integrate(1000, -1, 3);
    std::cout << "Integrate cos(x)*e^-x^2 from -1 to 3 (1000 steps): " << value << "\n";
    std::cout << "Difference from real value : " << realValue - value << "\n";
    std::cout << "Convergence: \n Steps \t Value \t Difference \t";
    for(int i = 100; i < 100000; i+=100){
        std::cout << i << "\t" << integrate(i, -1, 3) << "\t" << realValue - integrate(i, -1, 3) << "\n"; 
    }
    return 0;
}