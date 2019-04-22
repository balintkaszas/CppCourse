
#include <iostream>
#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>

double timeOfOperation(matrix<double> && m1, matrix<double> && m2) {
    auto t1 = std::chrono::high_resolution_clock::now();
	matrix<double> mat3 = m1 * m2;
    auto t2 = std::chrono::high_resolution_clock::now();
    return (static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count();
}

matrix<double> generateRandomMtx(int N, int seed = 10) {
    std::mt19937 gen(seed);
    std::normal_distribution<double> distr(100,20);
    return matrix<double>(matrix<double>::Idx1{}, N, [&](int i){return distr(gen);});
}

double minimumOfTrials(int numberOfTrials, int N, int seed = 10) {
    std::mt19937 gen(seed);
    std::normal_distribution<double> distr(100,25);

    std::vector<double> times;
    times.reserve(numberOfTrials);
    matrix<double> m1(matrix<double>::Idx1{}, N, [&](int i){return distr(gen);});

    for(int i = 0; i < numberOfTrials; i++) {

        matrix<double> m2(matrix<double>::Idx1{}, N, [&](int i){return distr(gen);});
        auto t1 = std::chrono::high_resolution_clock::now();
	    matrix<double> mat3 = m1 * m2;
        auto t2 = std::chrono::high_resolution_clock::now();
        times.push_back((static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count());  
    }
    return *std::min_element(times.begin(), times.end());
}

int main() {

    std::vector<int> dimensions;
    std::vector<double> times;
    for(int i = 4; i < 128; i+=4) {
        std::cout << i << " \n";
        dimensions.push_back(i);
        times.push_back(minimumOfTrials(10, i));
    }

    for(int i = 128; i <= 512; i+=32) {
        std::cout << i << " \n";
        dimensions.push_back(i);
        times.push_back(minimumOfTrials(10, i));
    }
    int n = static_cast<int>(times.size());
	std::ofstream output;
  	output.open("matmul_times.txt");
  	for(int i=0;i<n;i++){output << dimensions[i] << "\t" <<std::setprecision(16)<< times[i] << std::endl;}  
	output.close();    
    return 0;
}