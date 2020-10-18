#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<algorithm>

using namespace std;

vector <string>
Compostionk(string Text , unsigned int k)
{
    vector <string> Kmers;
    for (int i = 0 ; i < Text.length() - k + 1  ; i++)
    {
        string Kmer = Text.substr(i,k);
        Kmers.push_back(Kmer);
    }

    return Kmers;
}

int main ()
{
    ofstream myfile ("aa.txt");

    string Text;
    unsigned int k;
    cin >> k;
    // Input String here as cin takes limited to 4094 char
    Text = "";
    vector <string> Kmers = Compostionk(Text , k);
    for (int i = 0 ; i < Kmers.size() ; i++)
    {
        if (myfile.is_open() && i < Kmers.size()-1)
        {
        myfile << Kmers[i] << endl;
        continue;
        }
        myfile << Kmers[i] ;
        
        
    }
}

// Tested And Proved