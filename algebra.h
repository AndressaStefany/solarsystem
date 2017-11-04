//
// Created by vitor on 04/11/17.
//

#ifndef RACEGAME_ALGEBRA_H
#define RACEGAME_ALGEBRA_H

#include <iostream>
using namespace std;

class vec3 {
    double n[3];
public:
    vec3(double x,double y,double z);
    double& operator[](int i);

    vec3& operator=(const vec3 &a);
    vec3& operator+=(const vec3 &a);
    vec3& operator-=(const vec3 &a);
    vec3& operator*=(double k);
    vec3& operator/=(double k);

    friend vec3 operator+(const vec3& a,const vec3& b);
    friend vec3 operator-(const vec3& a);
    friend vec3 operator-(const vec3& a, const vec3& b);
    friend vec3 operator*(const vec3& a, double k);
    friend vec3 operator*(double k, const vec3& a);

    friend ostream& operator << (ostream& out, vec3& a);
    friend istream& operator >> (istream& in, vec3& a);
};


#endif //RACEGAME_ALGEBRA_H
