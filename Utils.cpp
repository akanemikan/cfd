#include "Utils.h"

source& operator+=(source &self, const source &other){
  forEach(self, i)
    self[i] += other[i];
  return self;
}

source& operator/=(source &self, double d){
  forEach(self, i)
    self[i] /= d;
  return self;
}

source& operator/=(source &self, isource &other){
  forEach(self, i)
    self[i] /= other[i];
  return self;
}

source operator^(const source &a, const source &b){
    source v(3);
    v[0] = a[1]*b[2] - a[2]*b[1];
    v[1] = a[2]*b[0] - a[0]*b[2]; 
    v[2] = a[0]*b[1] - a[1]*b[0]; 
    return v;
}

double operator&(const source &a, const source &b){
    double sum;
    forEach(a, i)
        sum += a[i]*b[i];
    return sum;
}

source operator+(const source &a, const source &b){
  source v(3);
  forEach(a, i)
    v[i] = a[i] + b[i];
  return v;
}

source operator-(const source &a,const  source &b){
  source v(3);
  forEach(a, i)
    v[i] = a[i] - b[i];
  return v;
}

source operator*(const source &a, double b){
  source v(3);
  forEach(a, i)
    v[i] = a[i]*b;
  return v;
}

source operator*(double a, const source &b){
  source v(3);
  forEach(b, i)
    v[i] = a*b[i];
  return v;
}

source operator/(const source &a, double b){
  source v(3);
  forEach(a, i)
    v[i] = a[i]/b;
  return v;
}

double magS(source &v){
    double s = 0.0;
    forEach(v, i)
        s += v[i]*v[i];
    return sqrt(s);
}

double calcDistance(source &p1, source &p2){
    double d = 0.0;
    for(int i=0; i<3; i++){
        double delta = p1[i] - p2[i];
        d += delta*delta;
    }
    return sqrt(d);
}
