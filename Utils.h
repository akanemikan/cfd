#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Source;

#define forEach(v, i) for(int i=0; i<v.size(); i++)

void show(const Matrix &v);
#endif
