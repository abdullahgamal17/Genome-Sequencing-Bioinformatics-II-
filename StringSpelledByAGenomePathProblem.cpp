#include <vector>
#include <string>
#include <iostream>

using namespace std;

string
Prefix(string Text)
{
    string Prefix = Text.substr(1,(Text.length()-1));
    return Prefix;
}

string 
Suffix(string Text)
{
    string suffix = Text.substr(0,(Text.length()-1));
    return suffix;
}

vector <string>
InputKmers(unsigned int NumberofKmers )
{
    vector <string> Kmers;
    for(int i = 0 ; i < NumberofKmers ; i++)
    {
        string Kmer;
        cin >> Kmer;
        Kmers.push_back(Kmer);
    }
    return Kmers;
}

string
StringSpelledByAGenomePathProblem(vector <string> Kmers)
{
    unsigned int NumberOfKmers = Kmers.size();
    string Answer;
    unsigned int LengthOfKmer = Kmers[0].length();

    for ( int i = 0 ; i < NumberOfKmers - 1; i++ )
    {
        if(i == 0)
        {
            Answer = Kmers[0];
        }
        if (Answer.substr((i+1),(Answer.length()-1)) == Kmers[i+1].substr(0,Kmers[i+1].length() - 1))
        {
            Answer += Kmers[i+1][Kmers[i+1].length()-1];
        }
        
    }

    return Answer;
       
}

int main()
{
    unsigned int NumberofKmers;
    cin >> NumberofKmers;
    vector <string> Kmers = InputKmers(NumberofKmers);
    cout << StringSpelledByAGenomePathProblem(Kmers);
}

//Tested And Proved