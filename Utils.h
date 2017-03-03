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

template<class T>
void showMatrix(const T &v){
    forEach(v,i){
        forEach(v[i],j){
            cout << v[i][j] << endl;
        }
    }
}

template<class T>
void showSource(const T &v){
    forEach(v, i){
        cout << v[i] << endl;
    }
}

#endif
