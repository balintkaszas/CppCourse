
#pragma once
#include <iostream>
#include <cmath>


template<typename T>
struct Vector2d
{
    T x,y;


    Vector2d<T>& operator+=( const Vector2d<T> & v){
        x += v.x;
        y += v.y;
        return *this;
    };

    
    Vector2d<T>& operator-=( const Vector2d<T> & v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vector2d<T>& operator*=( const T scalar){ //feltéve hogy T skalár tipus
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2d<T>& operator/=( const T scalar){
        x /= scalar;
        y /= scalar;
        return *this;
    }
};
template<typename T>
Vector2d<T> operator+( const Vector2d<T> & a, const Vector2d<T> & b)  {
    return Vector2d<T>{ a.x + b.x, a.y + b.y };
}

template<typename T>
Vector2d<T> operator-( const Vector2d<T> & a, const Vector2d<T> & b) {
    return Vector2d<T>{ a.x - b.x, a.y - b.y };
}

template<typename T>
Vector2d<T> operator*( const T scalar, const Vector2d<T> & b) {
    return Vector2d<T>{ scalar * b.x, scalar * b.y };
}
template<typename T>
Vector2d<T> operator*( const Vector2d<T> & b, const T scalar ) {
    return Vector2d<T>{ b.x * scalar,  b.y * scalar };
}

template<typename T>
Vector2d<T> operator/( const Vector2d<T> & b, const T scalar ){
    return Vector2d<T>{  b.x / scalar, b.y  / scalar};
}

template<typename T>
T dot(const Vector2d<T> & a, const Vector2d<T> & b) { //Skalar szorzat legyen valos. 
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T sqlength(const Vector2d<T> & a){
    return dot<T>(a, a);
}


template<typename T>
T length(const Vector2d<T> & a){
    return std::sqrt(sqlength<T>(a));
}

template<typename T>
Vector2d<T> normalize(const Vector2d<T> & a){
    return a/length(a);
}




template<typename T>
std::ostream& operator<<( std::ostream& o, const Vector2d<T> & a){
    o << a.x << " \t " << a.y << "\n";
    return o;
}

template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T> & a){
    i >> a.x;
    i >> a.y;
    return i;
}