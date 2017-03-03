#include "Utils.h"

Source& operator+=(Source &self, Source &other){
  forEach(self, i)
    self[i] += other[i];
  return self;
}

Source& operator/=(Source &self, double d){
  forEach(self, i)
    self[i] /= d;
  return self;
}

Source operator^(Source &a, Source &b){
    Source v(3);
    v[0] = a[1]*b[2] - a[2]*b[1];
    v[1] = a[2]*b[0] - a[0]*b[2]; 
    v[2] = a[0]*b[1] - a[1]*b[0]; 
    return v;
}

Source operator+(Source &a, Source &b){
  Source v(3);
  forEach(a, i)
    v[i] = a[i] + b[i];
  return v;
}

Source operator-(Source &a, Source &b){
  Source v(3);
  forEach(a, i)
    v[i] = a[i] - b[i];
  return v;
}

Source operator*(Source &a, double b){
  Source v(3);
  forEach(a, i)
    v[i] = a[i]*b;
  return v;
}

Source operator/(Source &a, double b){
  Source v(3);
  forEach(a, i)
    v[i] = a[i]/b;
  return v;
}

double magS(Source &v){
    double s = 0.0;
    forEach(v, i)
        s += v[i]*v[i];
    return sqrt(s);
}
