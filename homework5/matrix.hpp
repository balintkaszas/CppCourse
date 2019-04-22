#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

//Helper functions:
namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_matrix1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_matrix2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

//Common lambdas:
inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };
inline auto sq = [](auto const& x){ return x * x  ; };


//Large Vector class:
//Assumptions:
//Implements a heap allocated mathematical vector
//Elements are copyable and need not to be move-aware
//No exceptional cases are not handled
template<typename T>
class matrix
{
	std::vector<T> data;
    int N;
    public:
    struct Idx1{};
    struct Idx2{};
	//constructors



    template<typename F>
	matrix(Idx1, int n, F f) // linear construction from f function
	{
		data.resize(sq(n));
		for(int i=0; i<sq(n); ++i){ data[i] = f(i); }
        N = n;
    }

	template<typename F>
	matrix(Idx2, int n, F f){ //2 index construction 
		data.resize(sq(n));
		for(int i=0; i<n; ++i){ 
                for(int j=0; j<n ; ++j){
                    data[i*n+j] = f(i,j);
                }
            }
        N = n;
    }

	//Default, Copy and Move constructors implemented by the compiler:
	matrix(): data{},N{0}{} //default const 
	matrix( matrix const& ) = default; //copy const
    matrix(matrix && m):   data{std::move(m.data)},  //move const
                            N{m.N} {m.N = 0; }
    matrix(int n, std::initializer_list<T> const& il):    data{il}, N{n}{};
	matrix(int n) { //empty constructor
		data.resize(sq(n));
        N = n;
    }
	//Copy and Move assignment operators implemented by the compiler:
	matrix<T>& operator=(matrix const&) = default;
    matrix<T>& operator=(matrix<T> && m) {
        if (this != &m) {
            data = std::move(m.data);
            N = m.N;
            m.N = 0;
        }
        return *this;
    }	
	//Indexing:
	T& operator[]( int i ) { 
		return data[i];
	}
    T const& operator[]( int i ) const { //read only
		return data[i];
	}
    T& operator()(int i, int j) {
		return data[N*i+j];
	}
    T const& operator()(int i, int j) const { //read only 
 		return data[N*i+j]; 
	}

    //Add/subtract/mult/div assignment operators:
	matrix<T>& operator+= (matrix<T> const& cpy) {
		detail::transform_matrix2(*this, cpy, *this, add);
		return *this;
    }
	matrix<T>& operator-= (matrix<T> const& cpy) {
		detail::transform_matrix2(*this, cpy, *this, sub);
		return *this;
    }
	matrix<T>& operator*= (T const& scl) {
		detail::transform_matrix1(*this, *this, [scl](T const& x){ return x * scl;} );
		return *this;
    }
	matrix<T>& operator/= (T const& scl) {
		detail::transform_matrix1(*this, *this, [scl](T const& x){ return x / scl;} );
		return *this;
	}

	
	// Methods
	//Number of elements of the Vector:
	int dimension() const {
		return static_cast<int>(N);
	}
	int size() const {
		return static_cast<int>(sq(N));
	}

	//begin and end for compatibility with STL:
	auto begin() {
		return data.begin();
	}

	auto cbegin() const {
		return data.cbegin();
	}

	auto end() {
		return data.end();
	}

	auto cend() const {
		return data.cend();
	}
};

//Addition operators 4 versions for all combinations of const& and &&:
//Same applies to the two argument operator-
template<typename T>
matrix<T> operator+( matrix<T> const& m1, matrix<T> const& m2 ) {
	matrix<T> result (m1.dimension());
	detail::transform_matrix2(m1, m2, result, add);
	return result;
}

template<typename T>
matrix<T>&& operator+( matrix<T>&& m1, matrix<T> const& m2 ) {
	detail::transform_matrix2(m1, m2, m1, add );
	return std::move(m1);
}

template<typename T>
matrix<T>&& operator+( matrix<T> const& m1, matrix<T>&& m2 ) {
	detail::transform_matrix2(m1, m2, m2, add );
	return std::move(m2);
}

template<typename T>
matrix<T>&& operator+( matrix<T>&& m1, matrix<T>&& m2 ) {
	detail::transform_matrix2(m1, m2, m1, add );
	return std::move(m1);
}

//subtract operator
template<typename T>
matrix<T> operator-( matrix<T> const& m1, matrix<T> const& m2 ) {
	matrix<T> result (m1.dimension());
	detail::transform_matrix2(m1, m2, result, sub);
	return result;
}

template<typename T>
matrix<T>&& operator-( matrix<T>&& m1, matrix<T> const& m2 ) {
	detail::transform_matrix2(m1, m2, m1, sub );
	return std::move(m1);
}

template<typename T>
matrix<T>&& operator-( matrix<T> const& m1, matrix<T>&& m2 ) {
	detail::transform_matrix2(m1, m2, m2, sub );
	return std::move(m2);
}

template<typename T>
matrix<T>&& operator-( matrix<T>&& m1, matrix<T>&& m2 ) {
	detail::transform_matrix2(m1, m2, m1, sub );
	return std::move(m1);
}

// multiply/divide by scalar:
template<typename T>
matrix<T> operator*( matrix<T>  const& m1,  T const& scl) {
	matrix<T> result (m1.dimension());
   	detail::transform_matrix1(m1, result, [scl](auto const& x){ return x * scl; });
    return result;
}
template<typename T>
matrix<T> operator*( T const& scl, matrix<T>  const& m1) {
	matrix<T> result (m1.dimension());
   	detail::transform_matrix1(m1, result, [scl](auto const& x){ return scl * x; });
	return result;
}
template<typename T>
matrix<T>&& operator*( matrix<T>&& m1,  T const& scl) {
    detail::transform_matrix1(m1, m1, [scl](T const& x){ return x * scl; });
    return std::move(m1);   
}
template<typename T>
matrix<T>&& operator*(T const& scl, matrix<T>&& m1 ) {
    detail::transform_matrix1(m1, m1, [scl](T const& x){ return  scl*x; });
    return std::move(m1);   
}
template<typename T>
matrix<T> operator/( matrix<T>  const& m1,  T const& scl)
{
	matrix<T> result (m1.dimension());
   	detail::transform_matrix1(m1, result, [scl](auto const& x){ return x / scl; });
    return result;
}
template<typename T>
matrix<T>&& operator/( matrix<T>&& m1,  T const& scl) {
    detail::transform_matrix1(m1, m1, [scl](T const& x){ return x / scl; });
    return std::move(m1);   
}


//matrix multiplication 
template<typename T>
matrix<T> operator*( matrix<T>  const& m1, matrix<T>  const& m2 ) { 
    int n = m1.dimension();
    matrix<T> result(n);
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                T sum = 0.0;
                for(int k=0;k<n;k++) {
                    sum += m1(i,k)*m2(k,j);
                }
                result(i,j) = sum;
        	}
		}
	return result;
}
//matrix multiplication with &&
template<typename T>
matrix<T>&& operator*( matrix<T>  && m1, matrix<T>  const& m2 ) { 
        int n = m2.dimension();
        std::vector<T> tmp(n);
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                T sum = 0.0;
                for(int k=0;k<n;k++) {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<n; l++) {
		        m1(i, l) = tmp[l];
	        }
        }
    return std::move(m1);
}

template<typename T>
matrix<T>&& operator*( matrix<T>  const& m1, matrix<T>  && m2 ) { 
        int n = m2.dimension();
        std::vector<T> tmp(n);
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                T sum = 0.0;
                for(int k=0;k<n;k++) {
                    sum += m1(j,k)*m2(k,i);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<n; l++) {
		        m2(l, i) = tmp[l];
	        }
        }
    return std::move(m2);
}

template<typename T>
matrix<T>&& operator*( matrix<T>  && m1, matrix<T>  && m2 )
{
        int n = m1.dimension();
        std::vector<T> tmp(n);
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                T sum = 0.0;
                for(int k=0;k<n;k++) {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<n; l++) {
		        m1(i, l) = tmp[l];
	        }
        }
    return std::move(m1);
}



template<typename T> 
std::ostream& operator<<( std::ostream& s, matrix<T> const& m ) { //output operator
    int n = m.dimension();
    //s << "Size: " <<  _dim << "x" << _dim << "\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            s << m(i,j) << " ";
        }
    s << "\n";
    }
    s << "\n";
    return s;
}