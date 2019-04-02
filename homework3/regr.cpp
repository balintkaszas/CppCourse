#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <functional>

auto square = [](auto const x){return x * x;};


template <typename T> double average(const T & X){
    size_t size = X.size();
    return std::accumulate( X.begin(), X.end(), 0.0)/size;
}


template <typename T> auto regression( T const &X, T const &Y){
    double xAvg = average(X);
    double yAvg = average(Y);
    //computing the numerator and denominator of m
    double numerator = std::inner_product (X.begin(), X.end(), Y.begin(), 0.0, std::plus<double>(), 
                [xAvg, yAvg](const auto x, const auto y){return (x - xAvg) * (y - yAvg);});
    double denominator = std::accumulate (X.begin(), X.end(), 0.0, [xAvg]( const auto a, const auto x){return a + square(x - xAvg);});
    double m = numerator / denominator;
    double b = yAvg - m * xAvg;

    //computing rsqr
    double covY = std::accumulate(Y.begin(),
                            Y.end(),
                            0.0,
                            [yAvg](auto a, auto const y){return a + square(y - yAvg);});
    double covX = std::accumulate(X.begin(),
                            X.end(),
                            0.0,
                            [xAvg](auto a, auto const x){return a + square(x - xAvg);});
                            
    double rDenominator = std::sqrt(covX*covY);

    double r = numerator / rDenominator;
    return std::array<double, 3> {m, b, r};
}


template <typename T> void test(const T & X, const T & Y, const double m, const double b, const double r){

    std::array<double, 3> result = regression(X, Y);
    std::cout << "m = " << result[0] << ", real m = " << m << ", difference:" << result[0] - m <<  "\n";
    std::cout << "b = " << result[1] << ", real b = " << b << ", difference:" << result[1] - b <<  "\n";
    std::cout << "r = " << result[2] << ", real r = " << r << ", difference:" << result[2] - r <<  "\n";
}

int main(){
    std::cout.precision(16);

    const std::vector<double> height {1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83};
    const std::vector<double> mass {52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46};
    test(height, mass, 61.27218654211063, -39.061955918843935, 0.9945837935768896);
    //reference values calculated by scipy.stats.linregress() and 
    // https://en.wikipedia.org/wiki/Simple_linear_regression#Fitting_the_regression_line
    return 0;

}