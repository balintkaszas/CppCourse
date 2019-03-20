#include <iostream>
#include "vector.hpp"
#include <cmath>

int main() {
    Vector2d<double> a{}, b{};
    const double pi = 3.1415926535897932;
    std::cout <<"Enter vector a:\n";
    std::cin >> a;
    std::cout <<"Enter vector b:\n";
    std::cin >> b;
    std::cout<<"a = " << a;
    std::cout<<"b = " << b;
    std::cout<<"a + b =" << a + b;
    std::cout<<"a - b =" << a - b;
    
    std::cout<<"a*pi = " << a * pi;
    std::cout<<"pi*a = " << pi*a;
    std::cout<<"a/pi = " << a/pi;
    std::cout<<"a/0 = " << a / 0.0;
    std::cout<<"<a, b> = " << dot(a,b) << "\n";
    std::cout<<"||a|| = " << length(a) << "\n";
    std::cout<<"<a, a> = " << sqlength(a) << "\n";
    std::cout<<"a/||a|| = " << normalize(a) << "\n";

    a+={1., 1.,};
    std::cout<<"a+=(1, 1) = "<<a;
    a-={4., 4.};
    std::cout<<"a-=(4, 4) = "<<a;
    a*=100.0;
    std::cout<<"a*=100.0 = "<<a;
    a/=100.0;
    std::cout<<"a/=100.0 = "<<a;
    return 0;
}