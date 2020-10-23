#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector <int>
FromAminoAcidsToMasses(string Peptide)
{
    vector <char> AminoAcids = {'G', 'A', 'S', 'P', 'V', 'T', 'C', 'I', 'L', 'N', 'D', 'K', 'Q', 'E', 'M', 'H', 'F', 'R', 'Y', 'W'};
    vector <int> AminoAcidsMasses = {57, 71, 87, 97, 99, 101, 103, 113, 113, 114, 115, 128, 128, 129, 131, 137, 147, 156, 163, 186};
    vector <int> Path;
    for (int i = 0; i < Peptide.length(); i++)
    {
        
        int PosofMass;
        char OnChar = Peptide[i];
        for (int j = 0; j < AminoAcids.size() ; j++)
        {
            char ComparedWith = AminoAcids[j];
            if (OnChar == ComparedWith)
            {
                PosofMass = j;
                Path.push_back(AminoAcidsMasses[PosofMass]);
                break;
            }
        }
    }
    return Path;
}

int main()
{
    string a;
    cin >> a;
    vector <int> aa = FromAminoAcidsToMasses(a);
    for (int i = 0; i < aa.size()-1; i++)
    {
        cout <<aa[i] <<"-";
    }
    cout << aa[aa.size()-1];
}
