#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

typedef vector<vector<double>> matrix;
typedef vector<vector<int>> imatrix;
typedef vector<double> source;
typedef vector<int> isource;
typedef vector<string> ssource;

#define forEach(v, i) for(int i=0; i<(int)v.size(); i++)

double magS(source &v);

source& operator+=(source &self, const source &other);

source& operator/=(source &self, double);

source operator+(const source &a, const source &b);

source operator-(const source &a, const source &b);

source operator*(const source &a, double b);

source operator*(double a, const source &b);

source operator/(const source &a, double b);

source operator^(const source &a, const source &b);

double operator&(const source &a, const source &b);

template<class T>
void showMatrix(const T &v){
    forEach(v,i){
        forEach(v[i],j){
            cout << v[i][j] << "\t";
        }
        cout << endl;
    }
}

template<class T>
void showSource(const T &v){
    forEach(v, i){
        cout << v[i] << endl;
    }
}

#endif
