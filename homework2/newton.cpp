#include <iostream>
#include <cmath>



template<typename F, typename Fd, typename T, typename B>
T Newton(F f, Fd df, T x0, B isLarge, const int maxIterations = 10){

    T x1 = x0;
    for( int i = 0; i < maxIterations; i++) {
        T correction = f(x0) / df(x0);
        if( ! isLarge(0, correction)){ break; } 
        x1 = x0 - correction;
        x0 = x1;
    }

    return x1;
}

auto f = [](double x){return x*x - 612.0;};
auto df = [](double x){return 2.0*x;};
auto check = [](double x0, double x1)
    {
        double tolerance = 1e-14;
        if(std::abs(x1 - x0) <= tolerance )
        {
            return false;   
        }
        else
        {
            return true; 
        }
    };

int main(){
    std::cout.precision(16);
    const double realValue = 24.738633753705963298928; 
    const double solution = Newton(f,df,1.0,check);
    std::cout << "Result of the iteration: " << solution << "\t Real solution: " << realValue << "\n" ;
    std::cout << "Difference: " << "\t " << solution - realValue << "\n";
    return 0;
}