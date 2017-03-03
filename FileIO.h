#ifndef __FILEIO_H_INCLUDED__
#define __FILEIO_H_INCLUDED__
#include "Utils.h"


template <class T>
void ReadFile(T &x, string filename);

void ReadElement(ifstream &ifs, vector<vector<double>> &x, int size, string filename);
void ReadElement(ifstream &ifs, vector<vector<int>> &x, int size, string filename);
void ReadElement(ifstream &ifs, vector<int> &x, int size, string filename);

int ReadSize(ifstream &ifs);
int ReadBracket(ifstream &ifs);

vector<string> ReadWord(ifstream &ifs);
vector<string> ReadWord(ifstream &ifs, string targetWord);

ifstream setFile(string filename);
ofstream setFile();

template<class T>
void Matches(string str, string str_re, T &v);

template <class T>
void ReadFile(T &x, string filename)
{
    string str;
    ifstream ifs = setFile(filename);
   
    int size = ReadSize(ifs);
    ReadBracket(ifs);
    ReadElement(ifs, x, size, filename);
    ReadBracket(ifs);
}

#endif
