#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

ofstream myfile ("aa.txt");

void
Debruijn(string text , unsigned int k)
{
    vector <string> Kmers;
    vector <string> adjacent;
    for (int i = 0 ; i < text.length() - k + 1 ; i++)
    {
        string main = text.substr(i,k-1);
        Kmers.push_back(main);
    }

    sort(Kmers.begin() , Kmers.end());
    Kmers.erase(unique(Kmers.begin(), Kmers.end()), Kmers.end());

    for (int i = 0 ; i < Kmers.size() ; i++)
    {
        string main = Kmers[i];
        adjacent.clear();
        for (int j = 0 ; j < text.length() - k + 1 ; j++)
        {
            string compared = text.substr(j , k -1);
            if (main == compared )
            {
                string adjacentwithmain = text.substr(j+1,k-1);
                adjacent.push_back(adjacentwithmain);
            }
        }

        myfile << main <<" -> ";
        

        for (int jj = 0 ; jj < adjacent.size() ; jj++)
        {
            if (adjacent.size() == 1)
            {
                myfile << adjacent[jj];
            }
            if (adjacent.size() > 1 && jj < adjacent.size() - 1)
            {
                myfile << adjacent[jj] << ",";
            }
            if (adjacent.size() > 1 && jj == adjacent.size()-1)
            {
                myfile << adjacent[jj];
            }
        }
        if (i < Kmers.size()-1)
        {
            myfile << "\n";
        }   
    }
}

int main ()
{
    unsigned int k ;
    string text ;
    cin >> k >>text;
    Debruijn(text,k);
}
//Tested and approved