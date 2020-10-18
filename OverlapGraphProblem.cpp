#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

 ofstream myfile ("aa.txt");

void
OverlapGraphProblem(vector <string> Kmers)
{
    sort(Kmers.begin() , Kmers.end());
    Kmers.erase(unique(Kmers.begin(), Kmers.end()), Kmers.end());
    for (int i = 0 ; i < Kmers.size() ; i++)
    {
        string main = Kmers[i];
        vector <string> overlapedwith;
        overlapedwith.clear();
        


        for (int j = 0 ; j < Kmers.size() ; j++)
        {
            
            
            if(main.substr(1,( main.length() - 1 ) ) == Kmers[j].substr(0, ( Kmers[j].length() - 1 )))
            {
                overlapedwith.push_back(Kmers[j]);
            }
        }
        if (overlapedwith.empty())
        {
            continue;
        }
        else
        {
            myfile << main << " -> ";
            for (int jj = 0 ; jj < overlapedwith.size() ; jj++)
            {
                if(overlapedwith.size() == 1 )
                {
                    myfile << overlapedwith[jj];
                }
                if(overlapedwith.size() > 1 && jj < ( overlapedwith.size() -1 ) )
                {
                    myfile << overlapedwith[jj] << ",";
                }
                if(overlapedwith.size() > 1 && jj == ( overlapedwith.size() -1 ) )
                {
                    myfile << overlapedwith[jj];
                }
            }
        }
        if (i < Kmers.size() - 1)
        {
            myfile << "\n";
        }
    }
}

int main ()
{
   
    vector <string> Kmers;
    for (int i = 0 ; i < 4976 ; i ++ )
    {
        string a;
        cin >> a;
        Kmers.push_back(a);
    }
    OverlapGraphProblem(Kmers);
}

//Tested And Proved