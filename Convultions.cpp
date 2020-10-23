#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector <int>
ParseIntoInt(string a)
{
    string rhs = a;
    vector <int> Result;
    int pos;
    while(pos != -1)
    {
        string delim = " ";
        pos = rhs.find(delim);
        string lhs;
        if (pos != string::npos)
        {
            lhs = rhs.substr(0,pos);
            Result.push_back(stoi(lhs));
            rhs = rhs.substr(pos+delim.length(), a.length()-1);
        }
        
        if (pos == string::npos)
        {
            Result.push_back(stoi(rhs));
        }
        
    }
    return Result;    
}


vector <int>
Convultions(vector <int> Spectrum)
{
    vector <int> ff ;
    ff = Spectrum;
    for (int i = Spectrum.size()-1; i > 1; i--)
    {
        int OnSpectrum = Spectrum[i];
        for (int j = 1; j < i; j++)
        {
            int minus = Spectrum[j];
            int Convultion = OnSpectrum - minus;
            ff.push_back(Convultion);
        }
    }
    sort(ff.begin(),ff.end());
    ff.erase(remove(ff.begin(),ff.end() , 0),ff.end());
    return ff;
}
int
main()
{
    string a ="0 86 160 234 308 320 382"; 
    vector <int> Spectrum =ParseIntoInt(a);
    vector <int> aa = Convultions(Spectrum);
    for (int i = 0; i < aa.size(); i++)
    {
        cout << aa[i] << " ";
    }
    
}