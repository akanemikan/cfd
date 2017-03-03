#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<vector<int>> iMatrix;
typedef vector<double> Source;
typedef vector<int> iSource;
typedef vector<string> sSource;

#define forEach(v, i) for(int i=0; i<v.size(); i++)

double magS(Source &v);

Source& operator+=(Source &self, Source &other);

Source& operator/=(Source &self, double);

Source operator+(Source &a, Source &b);

Source operator-(Source &a, Source &b);

Source operator*(Source &a, double b);

Source operator/(Source &a, double b);

Source operator^(Source &a, Source &b);

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
