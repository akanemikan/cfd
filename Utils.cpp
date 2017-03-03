#include "Utils.h"

void show(const Matrix &v){
    forEach(v, c){
            cout << v[c].size() << endl;
        forEach(v[c], r){
            cout << v[c][r] << endl;
        }
    }
}
