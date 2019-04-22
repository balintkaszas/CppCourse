
#pragma once
#include <iostream>
#include <cmath>
#include "vector.hpp"

template<typename T>
 bool isCorrect(const T refX, const T refY, const  Vector2d<T> & V, const double precision = 1e-10) {
    bool didItPass = true;
    if(std::abs(V.x - refX) > precision and std::abs(V.x - refY) > precision) {
        didItPass = false;
    }
    return didItPass;
}   


void TestFunction() {
    int numErrors = 0;

    Vector2d<double> a = {1., 2.};
    Vector2d<double> b = {3., 4.};
    a += b;
    if(!isCorrect<double>(4., 6., a)){numErrors += 1; std::cout << "Error in += operator \n";}
    a -= b;
    if(!isCorrect<double>(1., 2., a)){numErrors += 1; std::cout << "Error in -= operator \n";}
    a *= 2.;
    if(!isCorrect<double>(2., 4., a)){numErrors += 1; std::cout << "Error in *= operator \n";}
    a /= 2.;
    if(!isCorrect<double>(1., 2., a)){numErrors += 1; std::cout << "Error in /= operator \n";}

    Vector2d<double> result;
    result = a + b;
    if(!isCorrect<double>(4., 6., result)){numErrors += 1; std::cout << "Error in + operator \n";}
    result = a - b;
    if(!isCorrect<double>(-2., -2., result)){numErrors += 1; std::cout << "Error in - operator \n";}
    result = 2.*a;
    if(!isCorrect<double>(2., 4., result)){numErrors += 1; std::cout << "Error in left * operator \n";}
    result = a*2.;
    if(!isCorrect<double>(2., 4., result)){numErrors += 1; std::cout << "Error in right * operator \n";}
    result = a/2.;
    if(!isCorrect<double>(0.5, 1., result)){numErrors += 1; std::cout << "Error in / operator \n";}
    double dotproduct = dot(a, b);
    if(std::abs(dotproduct - 11.) > 1e-10){numErrors += 1; std::cout << "Error in dot() function \n";}
    double len = length(a);
    if(std::abs(len - std::sqrt(5)) > 1e-10){numErrors += 1; std::cout << "Error in length() function \n";}
    double sqlen = sqlength(a);
    if(std::abs(sqlen - 5.) > 1e-10){numErrors += 1; std::cout << "Error in sqlength() function \n";}
        
    Vector2d<double> norm = normalize(a);
    if(!isCorrect<double>(1./std::sqrt(5.), 2./std::sqrt(5.), norm)){numErrors += 1; std::cout << "Error in normalize() function \n";}

    std::cout << "\n Tests finished with " << numErrors << " errors. \n";
}