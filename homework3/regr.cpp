#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <functional>

template <typename T> double average(const T & X){
    size_t size = X.size();
    return std::accumulate( X.begin(), X.end(), 0.0)/size;
}


template <typename T> T multiply(const T & X, const T & Y){
    size_t size = X.size();
    T product(size);
    std::transform( X.begin(), X.end(), Y.begin(), product.begin(), [](const auto a, const auto b){return a*b;});
    return product;
}



template <typename T> auto regression( T const &X, T const &Y){
    size_t size = X.size();
    double xAvg = average(X);
    double yAvg = average(Y);
    std::vector<double> xNormed, yNormed; 
    xNormed.resize(size);
    yNormed.resize(size);
    //subtracting average values
    std::transform(X.begin(), X.end(), xNormed.begin(), [xAvg](const auto a){return a - xAvg;});
    std::transform(Y.begin(), Y.end(), yNormed.begin(), [yAvg](const auto a){return a - yAvg;});
    //computing the numerator and denominator of m
    double numerator = std::inner_product(xNormed.begin(), xNormed.end(), yNormed.begin(), 0.0);
    double denominator = std::inner_product(xNormed.begin(), xNormed.end(), xNormed.begin(), 0.0);
    double m = numerator / denominator;
    double b = yAvg - m * xAvg;

    //computing rsqr
    double xyAvg = average(multiply(X, Y));
    double xxAvg = average(multiply(X, X));
    double yyAvg = average(multiply(Y, Y));
    double rsq = ( xyAvg - xAvg * yAvg ) * ( xyAvg - xAvg * yAvg ) / ((xxAvg - xAvg * xAvg) * (yyAvg - yAvg * yAvg));
    return std::array<double, 3> {m, b, rsq};
}


template <typename T> void test(const T & X, const T & Y, const double m, const double b, const double rsq){

    std::array<double, 3> result = regression(X, Y);
    std::cout << "m = " << result[0] << ", real m = " << m << ", difference:" << result[0] - m <<  "\n";
    std::cout << "b = " << result[1] << ", real b = " << b << ", difference:" << result[1] - b <<  "\n";
    std::cout << "r^2 = " << result[2] << ", real r^2 = " << rsq << ", difference:" << result[2] - rsq <<  "\n";
}

int main(){
    std::cout.precision(16);

    const std::vector<double> height {1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83};
    const std::vector<double> mass {52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46};
    test(height, mass, 61.27218654211063, -39.061955918843935, 0.9945837935768896*0.9945837935768896);
    //reference values calculated by scipy.stats.linregress() and 
    // https://en.wikipedia.org/wiki/Simple_linear_regression#Fitting_the_regression_line
    return 0;

}