
#pragma once
#include <iostream>
#include <cmath>
#include "matrix.hpp"

template<typename T>
 bool areEqual(std::vector<T> reference, const  matrix<T> & m, const double precision = 1e-10) {
    
    return std::equal (m.cbegin(), m.cend(), reference.cbegin(), [=](const auto x, const auto y){return std::abs(x - y) < precision;}) ;
}  

 

void TestFunction() {
    int numErrors = 0;
    //Default constructor
    {
        matrix<int> m;
        if( m.size() != 0 or m.dimension() != 0 or m.begin() != m.end()) {
            numErrors++;
            std::cout << "Default constructor failed \n";
        }
    }

    // init. list constructor, indexing and iterators
    // if iterators are correct, areEqual() function is enough 
    {
		matrix<double> m(2,{1., 2., 3., 4.});
        if( m.size() != 4 or m.dimension() != 2) {
            numErrors++;
            std::cout << "initializer list constructor failed (size mismatch) \n";
        }
		if(m[0] != 1. or m[1] != 2. or m[2] != 3. or m[3] != 4.) {
            numErrors++;
            std::cout << "initializer list constructor failed (1d indexing) \n";
        }
		if(m(0,0) != 1. or m(0,1) != 2. or m(1,0) != 3. or m(1,1) != 4.) {
            numErrors++;
            std::cout << "initializer list constructor failed (2d indexing) \n";
        }
        auto itWrite = m.begin();
        auto itRead = m.cbegin();
        for(int j = 1; j < 5 ; ++j){
            if(*itWrite != j or *itRead != j) {
                numErrors++;
                std::cout << "Iterator failed " << *itWrite << " " << j << "\n";
            } 
            std::advance(itWrite, 1);
            std::advance(itRead, 1);
        }
    }
    std::cout << "Number of errors is " << numErrors << "\n"; 
}