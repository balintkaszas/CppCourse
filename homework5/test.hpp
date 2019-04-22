
#pragma once
#include <iostream>
#include <cmath>
#include "matrix.hpp"

template<typename T>
 bool areEqual(const std::vector<T> &reference, const  matrix<T> & m, const double precision = 1e-10) {
    
    return (m.size() == static_cast<int>( reference.size() )) and std::equal (m.cbegin(), m.cend(), reference.cbegin(), [=](const auto x, const auto y){return std::abs(x - y) < precision;}) ;
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
    // if iterators tests are passed, areEqual() function is enough 
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

    // Testing with std::equal
    {
        matrix <double> m(2,{1., 2., 3., 4.});
        if(!areEqual({1., 2., 3., 4.}, m) ){
            numErrors ++;
            std::cout << "std::equal failed \n";
        }

    }
    //Empty constructor
    {
        matrix<double> m(2);
        if( m.size() != 4 or !areEqual({0., 0., 0., 0.}, m)) {
            numErrors++;
            std::cout << "Empty constructor failed \n";
        }
    }
    //1d constructor
    {
        matrix<double> m(matrix<double>::Idx1{}, 3, [](const auto x){return 2*x;});
        if( m.size() != 9 or !areEqual({0., 2., 4., 6., 8., 10., 12., 14., 16.}, m)) {
            numErrors++;
            std::cout << "1D function constructor failed \n";
        }
    }

    //2d constructor
    {
        matrix<double> m(matrix<double>::Idx2{}, 3, [](const auto x, const auto y){return 2*x+y;});
        if( m.size() != 9 or !areEqual({0., 1., 2., 2., 3., 4., 4., 5., 6.}, m)) {
            numErrors++;
            std::cout << "2D function constructor failed \n";
        }
    }
    //copy constructor
	{
		matrix<double> a(3,{0., 1., 2., 3., 4., 5., 6., 7., 8. });
		matrix<double> b{a};
        if(a.size() != b.size() or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8.}, b)) {
            numErrors++;
            std::cout << "Copy constructor failed \n";      
        }
    }
    // move constructor 
    {
		matrix<double> a(3,{0., 1., 2., 3., 4., 5., 6., 7., 8.});
		matrix<double> b{std::move(a)};
        if(a.size() != 0 or b.size() != 9  or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8. }, b)) {
            numErrors++;
            std::cout << "Move constructor failed \n";      
        }
    }

    // assign operators
    {
		matrix<double> a(3,{0., 1., 2., 3., 4., 5., 6., 7., 8.});
		matrix<double> b, c;
        a = a;
        if(a.size() != 9 or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8. }, a)) {
            numErrors++;
            std::cout << "Self assignment failed \n";              
        }

        a = std::move(a);
        if(a.size() != 9 or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8. }, a)) {
            numErrors++;
            std::cout << "Self move assignment failed \n";              
        } 
        b = a;
        if( b.size() != 9  or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8. }, b)) {
            numErrors++;
            std::cout << "Assignment failed \n";      
        }
        c = std::move(a);
        if(a.size() != 0 or c.size() != 9  or !areEqual({0., 1., 2., 3., 4., 5., 6., 7., 8. }, c)) {
            numErrors++;
            std::cout << "Move assignment failed \n";      
        }
    }
    std::cout << "Number of errors is " << numErrors << "\n"; 
}