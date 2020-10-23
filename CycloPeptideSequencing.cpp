#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

vector <string>
CreateLinearSubPeptides(string Peptide)
{
    vector <string> LinearSubPeptides;
    for (int i = 1; i < Peptide.length(); i++)
    {
        int LengthOfSubPeptide = i;
        for (int j = 0; j <= Peptide.length() - LengthOfSubPeptide; j++)
        {
            string LinearSubPeptide = Peptide.substr(j,i);
            LinearSubPeptides.push_back(LinearSubPeptide);
        }
        
    }
    LinearSubPeptides.push_back(Peptide);
    return LinearSubPeptides;
}

vector <int>
CycloSpectrum(string Peptide)
{
    vector <string> SubPeptides = CreateLinearSubPeptides(Peptide);
    vector <char> AminoAcids = {'G', 'A', 'S', 'P', 'V', 'T', 'C', 'I', 'L', 'N', 'D', 'K', 'Q', 'E', 'M', 'H', 'F', 'R', 'Y', 'W'};
    vector <int> AminoAcidsMasses = {57, 71, 87, 97, 99, 101, 103, 113, 113, 114, 115, 128, 128, 129, 131, 137, 147, 156, 163, 186};
    vector <int> CycloSpectrum;
    CycloSpectrum.push_back(0);
    for (int i = 0; i < SubPeptides.size(); i++)
    {
        int SubPeptideMass = 0;
        for (int j = 0; j < SubPeptides[i].length(); j++)
        {
            char OnAminoAcid = SubPeptides[i][j];
            for (int jj = 0; jj < AminoAcids.size(); jj++)
            {
                if (AminoAcids[jj] == OnAminoAcid)
                {
                    int MassOfAminoAcid = AminoAcidsMasses[jj];
                    SubPeptideMass += MassOfAminoAcid;
                }   
            }
        }
        CycloSpectrum.push_back(SubPeptideMass);
    }
    sort(CycloSpectrum.begin() , CycloSpectrum.end());
    return CycloSpectrum;
}

vector
int main()
{
    vector <int> a;
    a = CycloSpectrum("NQEL");
    cout << "Hello World";
}