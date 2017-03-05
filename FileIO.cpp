#include "FileIO.h"


ifstream setFile(string filename)
{
    ifstream ifs(filename);
    if(ifs.fail())
    {
        cerr << "失敗" << endl;
    }
    return ifs;
}

ofstream setFile()
{
    ofstream ofs("result.vtk");
    if(ofs.fail())
    {
        cerr << "失敗" << endl;
    }
    return ofs;
}


int readSize(ifstream &ifs)
{
    string str;
    regex pointsize_re("^[0-9]+$");
    int point_size;
    while (getline(ifs, str))
    { 
        if(regex_match(str, pointsize_re))
        {
            sscanf(str.data(), "%d", &point_size);
            return point_size;
        }
    }
    return point_size;
}

void CheckType(ssource &v, string m){ v.push_back(m); }

void CheckType(isource &v, string m){ v.push_back(stoi(m)); }

void CheckType(source &v, string m){ v.push_back(stod(m)); }

void CheckType(int &v, string m){ v = stoi(m); }

template<class T>
void Matches(string str, string str_re, T &v)
{
    regex re(str_re);
    for(std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), re);
                            i != std::sregex_iterator();
                            ++i )
    {
        std::smatch m = *i;
        CheckType(v, m.str());
    }
}

vector<string> readWord(ifstream &ifs, string targetWord)
{
    string str;
    vector<string> v;
    string str_re="[A-Za-z0-9\\(\\)]+";
    while(getline(ifs, str))
    {
        v.clear();
        Matches(str, str_re, v);  
        if(v.size() > 0 && v[0] == targetWord){
            return v;
        }
    }
    return v;
}

vector<string> readWord(ifstream &ifs)
{
    string str;
    string str_re="[A-Za-z0-9\\(\\)]+";
    vector<string> v;
    while(getline(ifs, str))
    {
        Matches(str, str_re, v);  
        if(v.size() > 0)
            return v;
    }
    return v;
}

int readBracket(ifstream &ifs)
{
    string str;
    regex bracket_re("[\\(\\){}\\s]+");
    while (getline(ifs, str))
    { 
        if(regex_match(str, bracket_re))
        {
            return 1;
        }
    }
    return -1;
}

void readElement(ifstream &ifs, matrix &x, int size, string filename)
{
    string str;
    string str_re="[0-9.]+";
    x = matrix(size);
    for(int i=0; i<size; i++){
        getline(ifs, str);
        Matches(str, str_re, x[i]);  
    }
}

void readElement(ifstream &ifs, imatrix &x, int size, string filename)
{

    string str;
    string str_re="[0-9]+";
    x = imatrix(size);
    for(int i=0; i<size; i++){
        getline(ifs, str);
        Matches(str, str_re, x[i]);  
    }

}

void readElement(ifstream &ifs, isource &x, int size, string filename)
{
    string str;
    string str_re="[0-9.]+";
    x = isource(size);
    for(int i=0; i<size; i++){
        getline(ifs, str);
        Matches(str, str_re, x[i]);  
    }
}



