#ifndef __FILEIO_H_INCLUDED__
#define __FILEIO_H_INCLUDED__
#include "Utils.h"


template <class T>
void readFile(T &x, string filename);

void readElement(ifstream &ifs, matrix &x, int size, string filename);
void readElement(ifstream &ifs, imatrix &x, int size, string filename);
void readElement(ifstream &ifs, isource &x, int size, string filename);


int readSize(ifstream &ifs);
int readBracket(ifstream &ifs);

vector<string> readWord(ifstream &ifs);
vector<string> readWord(ifstream &ifs, string targetWord);

ifstream setFile(string filename);
ofstream setFile();

template<class T>
void Matches(string str, string str_re, T &v);

template <class T>
void readFile(T &x, string filename)
{
    string str;
    ifstream ifs = setFile(filename);
   
    int size = readSize(ifs);
    readBracket(ifs);
    readElement(ifs, x, size, filename);
    readBracket(ifs);
}

#endif
