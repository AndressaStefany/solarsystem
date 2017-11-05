//
// Created by vitor on 04/11/17.
//

#include "algebra.h"

vec3::vec3(double x, double y, double z) {
    n[0]= x;
    n[1]= y;
    n[2]= z;
}

vec3::vec3() {
    n[0]= 0;
    n[1]= 0;
    n[2]= 0;
}

double &vec3::operator[](int i) {
    return n[i];
}

vec3 &vec3::operator=(const vec3 &a) {
    n[0]= a.n[0];
    n[1]= a.n[1];
    n[2]= a.n[2];
    return *this;
}

vec3 &vec3::operator+=(const vec3 &a) {
    n[0]+= a.n[0];
    n[1]+= a.n[1];
    n[2]+= a.n[2];
    return *this;;
}

vec3 &vec3::operator-=(const vec3 &a) {
    n[0]-= a.n[0];
    n[1]-= a.n[1];
    n[2]-= a.n[2];
    return *this;
}

vec3 &vec3::operator*=(double k) {
    n[0]*=k;
    n[1]*=k;
    n[2]*=k;
    return *this;
}

vec3 &vec3::operator/=(double k) {
    n[0]/=k;
    n[1]/=k;
    n[2]/=k;
    return *this;
}

vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a.n[0]+b.n[0], a.n[1]+b.n[1], a.n[2]+b.n[2]);
}

vec3 operator-(const vec3 &a) {
    return vec3(-a.n[0], -a.n[1], -a.n[2]);
}

vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a.n[0]-b.n[0], a.n[1]-b.n[1], a.n[2]-b.n[2]);
}

vec3 operator*(const vec3 &a, double k) {
    return vec3(a.n[0]*k, a.n[1]*k, a.n[2]*k);
}

vec3 operator*(double k, const vec3 &a) {
    return vec3(k*a.n[0], k*a.n[1], k*a.n[2]);
}

ostream &operator<<(ostream &out, vec3 &a) {
    out << a.n[0] << " " << a.n[1] << " " << a.n[2] << " " << endl;
    return out;
}

istream &operator>>(istream &in, vec3 &a) {
    in >> a.n[0] >> a.n[1] >> a.n[2];
    return in;
}

vec2::vec2(double x, double y) {
    n[0]= x;
    n[1]= y;
}

double &vec2::operator[](int i) {
    return n[i];
}

vec2 &vec2::operator=(const vec2 &a) {
    n[0]= a.n[0];
    n[1]= a.n[1];
    return *this;
}

vec2 &vec2::operator+=(const vec2 &a) {
    n[0]+= a.n[0];
    n[1]+= a.n[1];
    return *this;
}

vec2 &vec2::operator-=(const vec2 &a) {
    n[0]-= a.n[0];
    n[1]-= a.n[1];
    return *this;
}

vec2 &vec2::operator*=(double k) {
    n[0]*=k;
    n[1]*=k;
    return *this;
}

vec2 &vec2::operator/=(double k) {
    n[0]/=k;
    n[1]/=k;
    return *this;
}

vec2 operator+(const vec2 &a, const vec2 &b) {
    return vec2(a.n[0]+b.n[0], a.n[1]+b.n[1]);
}

vec2 operator-(const vec2 &a) {
    return vec2(-a.n[0], -a.n[1]);
}

vec2 operator-(const vec2 &a, const vec2 &b) {
    return vec2(a.n[0]-b.n[0], a.n[1]-b.n[1]);
}

vec2 operator*(const vec2 &a, double k) {
    return vec2(k*a.n[0], k*a.n[1]);
}

vec2 operator*(double k, const vec2 &a) {
    return vec2(a.n[0]*k, a.n[1]*k);
}

ostream &operator<<(ostream &out, vec2 &a) {
    out << a.n[0] << " " << a.n[1] << endl;
    return out;
}

istream &operator>>(istream &in, vec2 &a) {
    in >> a.n[0] >> a.n[1];
    return in;
}

vec2::vec2() {
    n[0]= 0;
    n[1]= 1;
}
